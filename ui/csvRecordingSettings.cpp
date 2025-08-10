/** @file      csvRecordingSettings.cpp
 *  @brief     Source file for the CSV recording settings functions.
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

#include "csvRecordingSettings.h"
#include "../Libraries/lib.h"
#include "../backends/imgui.h"
#include "../backends/implot.h"
#include "settings.h"
#include "../pch/pch.h"
#include "../serial/csvStorage.h"
#include "../serial/serialComms.h"
#include "dataReceptionSettings.h"
#include <chrono>
#include <iomanip>
#include <sstream>

// Static variables for UI state
static char csvFilename[256] = "mscope.csv";
static char channelNames[3][64] = {
    "Channel_1", "Channel_2", "Channel_3"
};
static bool showChannelNames = false;
static bool useTimestampedFilename = true;

std::string getCSVFilename(void)
{
    if (useTimestampedFilename)
    {
        return generateTimestampedFilename("mscope");
    }
    return std::string(csvFilename);
}

std::vector<std::string> getChannelNames(void)
{
    std::vector<std::string> names;
    int numChannels = getNumberOfChannels();
    
    for (int i = 0; i < numChannels && i < 3; ++i)
    {
        names.push_back(std::string(channelNames[i]));
    }
    
    return names;
}

void csvRecordingSettings(void)
{
    if (ImGui::CollapsingHeader("CSV Recording Settings", ImGuiTreeNodeFlags_DefaultOpen))
    {
        // Filename input
        ImGui::Text("CSV Filename:");
        ImGui::Checkbox("Use timestamped filename", &useTimestampedFilename);
        
        if (!useTimestampedFilename)
        {
            ImGui::InputText("##CSVFilename", csvFilename, sizeof(csvFilename));
        }
        else
        {
            ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), 
                              "Will use: %s", generateTimestampedFilename("mscope").c_str());
        }
        
        // Channel names configuration
        int numChannels = getNumberOfChannels();
        if (numChannels > 0)
        {
            ImGui::Text("Channel Names (%d channels):", numChannels);
            
            if (ImGui::Button("Configure Channel Names"))
            {
                showChannelNames = !showChannelNames;
            }
            
            if (showChannelNames)
            {
                ImGui::BeginChild("ChannelNames", ImVec2(0, 150), true);
                for (int i = 0; i < numChannels && i < 3; ++i)
                {
                    std::string label = "Channel " + std::to_string(i + 1) + "##";
                    ImGui::InputText(label.c_str(), channelNames[i], sizeof(channelNames[i]));
                }
                ImGui::EndChild();
            }
        }
        else
        {
            ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.0f, 1.0f), 
                              "Set number of channels in Data Reception Settings first");
        }
        
        ImGui::Separator();
        
        // Recording controls
        bool isRecording = isCSVRecording();
        
        if (!isRecording)
        {
            if (ImGui::Button("Start CSV Recording", ImVec2(150, 30)))
            {
                if (numChannels > 0)
                {
                    std::string filename = getCSVFilename();
                    std::vector<std::string> names = getChannelNames();
                    
                    if (startCSVRecording(filename, names))
                    {
                        ImGui::OpenPopup("Recording Started");
                    }
                    else
                    {
                        ImGui::OpenPopup("Recording Failed");
                    }
                }
            }
        }
        else
        {
            if (ImGui::Button("Stop CSV Recording", ImVec2(150, 30)))
            {
                stopCSVRecording();
            }
        }
        
        // Recording status
        if (isRecording)
        {
            ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Recording to: %s", 
                              getCSVCurrentFilename().c_str());
            ImGui::Text("Data points recorded: %zu", getCSVRecordedDataPoints());
            
            // Add a visual indicator
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "REC");
        }
        else
        {
            ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), "Not recording");
        }
        
        // Popup messages
        if (ImGui::BeginPopupModal("Recording Started", NULL, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::Text("CSV recording started successfully!");
            if (ImGui::Button("OK", ImVec2(120, 0)))
            {
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }
        
        if (ImGui::BeginPopupModal("Recording Failed", NULL, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::Text("Failed to start CSV recording!");
            ImGui::Text("Check if the file can be created and is not in use.");
            if (ImGui::Button("OK", ImVec2(120, 0)))
            {
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }
    }
} 