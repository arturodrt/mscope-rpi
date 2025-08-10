/** @file      visualizer.cpp
 *  @brief     Source file for the visualizer functions.
 *  @author    arturodlr
 *  @date      Created on 2024/02/22
 *
 *  This software is the exclusive property of Cortx and is provided
 *  under strict confidentiality. It is intended for use solely by authorized
 *  personnel of Cortx and is protected by intellectual property laws.
 *  Unauthorized use, reproduction, or distribution in whole or in part is
 *  scrictly prohibited.
 *
 *  COPYRIGHT NOTICE: 2025 Cortx, Montreal, QC. All rights reserved.
 */

#include "visualizer.h"
#include "../serial/serialComms.h"
#include "../backends/imgui.h"
#include "../backends/implot.h"
#include "serialSettings.h"
#include <mutex>
#include "serialTerminal.h"
#include "viewerSettings.h"
#include "generalSettings.h"
#include "dataReceptionSettings.h"
#include <iostream> // For std::cerr and std::endl
/* Mutex for floatData */
std::mutex dataMutex;

// Static variables for plot view management
static int currentPlotView = 0; // 0 = combined view, 1+ = individual channels

// Function to render a single channel plot
void renderChannelPlot(int channelIndex, const std::string& channelName, const ImVec4& color)
{
    if (channelIndex < channelsData.size() && !channelsData[channelIndex].empty())
    {
        if (channelsData[channelIndex].size() == xValues.size())
        {
            ImPlot::PushStyleColor(ImPlotCol_Line, color);
            ImPlot::PlotLine(channelName.c_str(), xValues.data(),
                             channelsData[channelIndex].data(),
                             static_cast<int>(xValues.size()));
            ImPlot::PopStyleColor();
        }
    }
}

// Function to render statistics for a channel
void renderChannelStatistics(int channelIndex)
{
    if (channelIndex < channelsData.size() && !channelsData[channelIndex].empty())
    {
        const std::vector<float>& channelData = channelsData[channelIndex];
        
        if (channelData.size() == xValues.size())
        {
            ImGui::Separator();
            ImGui::Text("Channel Statistics:");
            
            // Calculate statistics
            float minVal = channelData[0], maxVal = channelData[0];
            float sum = 0.0f;
            
            for (size_t i = 0; i < channelData.size(); ++i)
            {
                if (channelData[i] < minVal) minVal = channelData[i];
                if (channelData[i] > maxVal) maxVal = channelData[i];
                sum += channelData[i];
            }
            
            float avg = sum / channelData.size();
            
            // Display statistics
            ImGui::Text("Min: %.6f", minVal);
            ImGui::Text("Max: %.6f", maxVal);
            ImGui::Text("Avg: %.6f", avg);
            ImGui::Text("Range: %.6f", maxVal - minVal);
            ImGui::Text("Data Points: %zu", channelData.size());
            
            if (!xValues.empty())
            {
                float timeSpan = xValues.back() - xValues.front();
                ImGui::Text("Time Span: %.3f s", timeSpan);
            }
        }
    }
}

void plot(void)
{
  std::lock_guard<std::mutex> lock(dataMutex);
  OrbCode_t orbCode = Success;

  if (orbCode == InvalidData && !isSerialPortOpened())
  {
    serialReadingsError();
    return;
  }

  if (isSerialPortOpened())
  {
    serialTerminal();

    // Get the main dockspace ID
    ImGuiID dockspaceId = ImGui::GetID("InvisibleWindowDockSpace");
    
    // Set the main Live View window to dock into the main dockspace
    ImGui::SetNextWindowDockID(dockspaceId, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiCond_FirstUseEver);
    
    ImGui::Begin("Live View");
    
    // Plot area for combined view only
    ImVec2 plotSize = ImGui::GetContentRegionAvail();
    std::string plotTitle = "Combined View";

    if (ImPlot::BeginPlot(plotTitle.c_str(), plotSize))
    {
      if (isThemeDarkSelected())
      {
        ImPlot::StyleColorsDark();
      }
      else
      {
        ImPlot::StyleColorsLight();
      }

      // Set up axes
      ImPlot::SetupAxes("Time (s)", "Value");

      const int numChannels = channelsData.size();
      std::vector<std::string> labels;
      getDataLabels(labels);

      const ImVec4 colors[] = {
          ImVec4(1.0f, 0.400f, 0.400f, 1.0f), // Red
          ImVec4(0.0f, 0.600f, 0.200f, 1.0f), // Green
          ImVec4(0.0f, 0.541f, 0.902f, 1.0f), // Blue
          ImVec4(1.0f, 0.843f, 0.0f, 1.0f),   // Yellow
          ImVec4(0.580f, 0.0f, 0.827f, 1.0f), // Purple
          ImVec4(1.0f, 0.647f, 0.0f, 1.0f),   // Orange
          ImVec4(0.0f, 0.808f, 0.820f, 1.0f), // Cyan
          ImVec4(0.5f, 0.0f, 0.5f, 1.0f),     // Magenta
          ImVec4(0.722f, 0.525f, 0.043f, 1.0f), // Brown
          ImVec4(0.5f, 0.5f, 0.5f, 1.0f),     // Gray
      };

      // Check if xValues is not empty
      if (!xValues.empty())
      {
        // Combined view - plot all channels
        for (int i = 0; i < numChannels && i < labels.size(); ++i)
        {
          renderChannelPlot(i, labels[i], colors[i % (sizeof(colors) / sizeof(colors[0]))]);
        }
      }
      else
      {
        std::cerr << "No x-axis data available" << std::endl;
      }

      ImPlot::EndPlot();
    }

    ImGui::End();
    
    // Render individual plot windows for visible channels
    renderIndividualPlotWindows();
  }
}

int getCurrentPlotView(void)
{
    return currentPlotView;
}

void setCurrentPlotView(int view)
{
    currentPlotView = view;
}

int getNumberOfPlotViews(void)
{
    int numChannels = getNumberOfChannels();
    return numChannels + 1; // +1 for combined view
}

std::string getPlotViewName(int viewIndex)
{
    if (viewIndex == 0)
    {
        return "Combined View";
    }
    else
    {
        std::vector<std::string> labels;
        getDataLabels(labels);
        int channelIndex = viewIndex - 1;
        if (channelIndex < labels.size())
        {
            return labels[channelIndex];
        }
        else
        {
            return "Channel " + std::to_string(viewIndex);
        }
    }
}

void renderIndividualPlotWindows(void)
{
    std::vector<bool> channelVisibility;
    getChannelVisibility(channelVisibility);
    
    std::vector<std::string> labels;
    getDataLabels(labels);
    
    const ImVec4 colors[] = {
        ImVec4(1.0f, 0.400f, 0.400f, 1.0f), // Red
        ImVec4(0.0f, 0.600f, 0.200f, 1.0f), // Green
        ImVec4(0.0f, 0.541f, 0.902f, 1.0f), // Blue
        ImVec4(1.0f, 0.843f, 0.0f, 1.0f),   // Yellow
        ImVec4(0.580f, 0.0f, 0.827f, 1.0f), // Purple
        ImVec4(1.0f, 0.647f, 0.0f, 1.0f),   // Orange
        ImVec4(0.0f, 0.808f, 0.820f, 1.0f), // Cyan
        ImVec4(0.5f, 0.0f, 0.5f, 1.0f),     // Magenta
        ImVec4(0.722f, 0.525f, 0.043f, 1.0f), // Brown
        ImVec4(0.5f, 0.5f, 0.5f, 1.0f),     // Gray
    };
    
    // Get the main dockspace ID
    ImGuiID dockspaceId = ImGui::GetID("InvisibleWindowDockSpace");
    
    // Render individual windows for visible channels only
    for (int i = 0; i < channelVisibility.size() && i < labels.size(); ++i)
    {
        if (channelVisibility[i])
        {
            // Ensure label is never empty
            std::string safeLabel = labels[i];
            if (safeLabel.empty())
            {
                safeLabel = "Channel " + std::to_string(i + 1);
            }
            std::string windowTitle = safeLabel + " - Individual View";
            
            // Set the window to dock into the main dockspace
            ImGui::SetNextWindowDockID(dockspaceId, ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_FirstUseEver);
            
            // Use docking-compatible window flags
            ImGuiWindowFlags windowFlags = ImGuiWindowFlags_None;
            
            if (ImGui::Begin(windowTitle.c_str(), nullptr, windowFlags))
            {
                ImVec2 plotSize = ImGui::GetContentRegionAvail();
                
                if (ImPlot::BeginPlot(safeLabel.c_str(), plotSize))
                {
                    if (isThemeDarkSelected())
                    {
                        ImPlot::StyleColorsDark();
                    }
                    else
                    {
                        ImPlot::StyleColorsLight();
                    }
                    
                    ImPlot::SetupAxes("Time (s)", safeLabel.c_str());
                    
                    if (!xValues.empty())
                    {
                        renderChannelPlot(i, safeLabel, colors[i % (sizeof(colors) / sizeof(colors[0]))]);
                    }
                    
                    ImPlot::EndPlot();
                }
                
                // Display statistics for this channel
                renderChannelStatistics(i);
            }
            ImGui::End();
        }
    }
}

int getNumberOfVisiblePlotViews(void)
{
    std::vector<bool> channelVisibility;
    getChannelVisibility(channelVisibility);
    
    int count = 0;
    for (bool visible : channelVisibility)
    {
        if (visible) count++;
    }
    return count;
}

std::string getVisiblePlotViewName(int visibleIndex)
{
    std::vector<bool> channelVisibility;
    getChannelVisibility(channelVisibility);
    
    std::vector<std::string> labels;
    getDataLabels(labels);
    
    int visibleCount = 0;
    for (int i = 0; i < channelVisibility.size() && i < labels.size(); ++i)
    {
        if (channelVisibility[i])
        {
            if (visibleCount == visibleIndex)
            {
                return labels[i];
            }
            visibleCount++;
        }
    }
    return "";
}

int getVisiblePlotViewChannelIndex(int visibleIndex)
{
    std::vector<bool> channelVisibility;
    getChannelVisibility(channelVisibility);
    
    int visibleCount = 0;
    for (int i = 0; i < channelVisibility.size(); ++i)
    {
        if (channelVisibility[i])
        {
            if (visibleCount == visibleIndex)
            {
                return i;
            }
            visibleCount++;
        }
    }
    return -1;
}
