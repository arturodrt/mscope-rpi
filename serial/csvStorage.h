/** @file      csvStorage.h
 *  @brief     Header file for CSV data storage functions.
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

#ifndef CSV_STORAGE_H
#define CSV_STORAGE_H

#include <string>
#include <vector>
#include <fstream>
#include <mutex>
#include <chrono>
#include "../Libraries/lib.h"

class CSVStorage
{
public:
    CSVStorage();
    ~CSVStorage();

    /**
     * @brief Starts recording data to a CSV file
     * @param filename The name of the CSV file to create
     * @param channelNames Vector of channel names for CSV headers
     * @return true if successfully started, false otherwise
     */
    bool startRecording(const std::string& filename, const std::vector<std::string>& channelNames);

    /**
     * @brief Stops recording and closes the CSV file
     */
    void stopRecording();

    /**
     * @brief Writes a data row to the CSV file
     * @param timestamp The timestamp for this data point
     * @param data Vector of data values for each channel
     * @return true if successfully written, false otherwise
     */
    bool writeDataRow(double timestamp, const std::vector<float>& data);

    /**
     * @brief Checks if currently recording
     * @return true if recording, false otherwise
     */
    bool isRecording() const;

    /**
     * @brief Gets the current recording filename
     * @return The current filename or empty string if not recording
     */
    std::string getCurrentFilename() const;

    /**
     * @brief Gets the number of data points recorded so far
     * @return Number of data points recorded
     */
    size_t getRecordedDataPoints() const;

private:
    std::ofstream csvFile;
    std::string currentFilename;
    bool recording;
    size_t dataPointsRecorded;
    std::mutex fileMutex;
    std::chrono::steady_clock::time_point recordingStartTime;

    /**
     * @brief Writes the CSV header with timestamp and channel names
     * @param channelNames Vector of channel names
     */
    void writeHeader(const std::vector<std::string>& channelNames);

    /**
     * @brief Formats timestamp for CSV output
     * @param timestamp The timestamp to format
     * @return Formatted timestamp string
     */
    std::string formatTimestamp(double timestamp) const;
};

// Global instance
extern CSVStorage g_csvStorage;

// Global functions for easy access
bool startCSVRecording(const std::string& filename, const std::vector<std::string>& channelNames);
void stopCSVRecording();
bool writeCSVDataRow(double timestamp, const std::vector<float>& data);
bool isCSVRecording();
std::string getCSVCurrentFilename();
size_t getCSVRecordedDataPoints();

/**
 * @brief Generates a timestamped filename for CSV recording
 * @param baseName Base name for the file (without extension)
 * @return Timestamped filename with .csv extension
 */
std::string generateTimestampedFilename(const std::string& baseName = "mscope");

#endif // CSV_STORAGE_H 