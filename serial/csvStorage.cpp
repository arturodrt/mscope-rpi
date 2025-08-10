/** @file      csvStorage.cpp
 *  @brief     Source file for CSV data storage functions.
 *  @author    arturodlrios
 *  @date      Created on 2024/12/19
 *
 *  This software is the exclusive property of Cortx and is provided
 *  under strict confidentiality. It is intended for use solely by authorized
 *  personnel of Cortx and is protected by intellectual property laws.
 *  Unauthorized use, reproduction, or distribution in whole or in part is
 *  strictly prohibited.
 *
 *  COPYRIGHT NOTICE: 2025 Cortx, Montreal, QC. All rights reserved.
 */

#include "csvStorage.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <filesystem>

// Global instance
CSVStorage g_csvStorage;

CSVStorage::CSVStorage() 
    : recording(false), dataPointsRecorded(0)
{
}

CSVStorage::~CSVStorage()
{
    if (recording)
    {
        stopRecording();
    }
}

bool CSVStorage::startRecording(const std::string& filename, const std::vector<std::string>& channelNames)
{
    std::lock_guard<std::mutex> lock(fileMutex);
    
    if (recording)
    {
        std::cerr << "CSV recording already in progress. Stop current recording first." << std::endl;
        return false;
    }

    // Validate filename
    if (filename.empty())
    {
        std::cerr << "CSV filename cannot be empty." << std::endl;
        return false;
    }

    // Open the CSV file
    csvFile.open(filename);
    if (!csvFile.is_open())
    {
        std::cerr << "Failed to open CSV file: " << filename << std::endl;
        return false;
    }

    currentFilename = filename;
    recording = true;
    dataPointsRecorded = 0;
    recordingStartTime = std::chrono::steady_clock::now();

    // Write the header
    writeHeader(channelNames);

    std::cout << "Started CSV recording to: " << filename << std::endl;
    return true;
}

void CSVStorage::stopRecording()
{
    std::lock_guard<std::mutex> lock(fileMutex);
    
    if (!recording)
    {
        return;
    }

    if (csvFile.is_open())
    {
        csvFile.close();
    }

    std::cout << "Stopped CSV recording. Total data points recorded: " << dataPointsRecorded << std::endl;
    
    recording = false;
    currentFilename.clear();
}

bool CSVStorage::writeDataRow(double timestamp, const std::vector<float>& data)
{
    std::lock_guard<std::mutex> lock(fileMutex);
    
    if (!recording || !csvFile.is_open())
    {
        return false;
    }

    try
    {
        // Write timestamp first
        csvFile << formatTimestamp(timestamp);
        
        // Write data values
        for (size_t i = 0; i < data.size(); ++i)
        {
            csvFile << "," << std::fixed << std::setprecision(6) << data[i];
        }
        
        csvFile << std::endl;
        dataPointsRecorded++;
        
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error writing to CSV file: " << e.what() << std::endl;
        return false;
    }
}

bool CSVStorage::isRecording() const
{
    return recording;
}

std::string CSVStorage::getCurrentFilename() const
{
    return currentFilename;
}

size_t CSVStorage::getRecordedDataPoints() const
{
    return dataPointsRecorded;
}

void CSVStorage::writeHeader(const std::vector<std::string>& channelNames)
{
    csvFile << "Timestamp";
    for (const auto& channelName : channelNames)
    {
        csvFile << "," << channelName;
    }
    csvFile << std::endl;
}

std::string CSVStorage::formatTimestamp(double timestamp) const
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(6) << timestamp;
    return oss.str();
}

// Global function implementations
bool startCSVRecording(const std::string& filename, const std::vector<std::string>& channelNames)
{
    return g_csvStorage.startRecording(filename, channelNames);
}

void stopCSVRecording()
{
    g_csvStorage.stopRecording();
}

bool writeCSVDataRow(double timestamp, const std::vector<float>& data)
{
    return g_csvStorage.writeDataRow(timestamp, data);
}

bool isCSVRecording()
{
    return g_csvStorage.isRecording();
}

std::string getCSVCurrentFilename()
{
    return g_csvStorage.getCurrentFilename();
}

size_t getCSVRecordedDataPoints()
{
    return g_csvStorage.getRecordedDataPoints();
}

std::string generateTimestampedFilename(const std::string& baseName)
{
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    auto tm = *std::localtime(&time_t);
    
    std::ostringstream oss;
    oss << baseName << "_" 
        << std::put_time(&tm, "%Y%m%d_%H%M%S") 
        << ".csv";
    
    return oss.str();
} 