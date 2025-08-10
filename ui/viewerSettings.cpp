/** @file      viewerSettings.cpp
 *  @brief     Source file for the viewer settings functions.
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

#include "settings.h"
#include "../backends/imgui.h"
#include "../backends/implot.h"
#include "viewerSettings.h"
#include "../Libraries/lib.h"
#include <algorithm>
#include "dataReceptionSettings.h"
#include <cstring>

static int bufferDataSize = 1000; // Default to 1000 elements

static std::vector<std::string> dataLabels;
static bool channelVisibility[3] = {false, false, false}; // Track which channels are visible for individual plots (Lite version: 3 channels)

/**
 * @brief Displays an ImGui widget to set the data size for a buffer, clamping
 * the value within a specified range.
 *
 * This function creates an ImGui widget that allows the user to input an
 * integer value (`bufferDataSize`) to set the data size for a buffer. The input
 * field restricts the value to be within the range [min, max]. The function
 * also clamps the input value to ensure it does not exceed the specified
 * bounds.
 */
void prv_imGuiSetDataSizeWidget(void);

int viewerDataSize(void)
{
  return bufferDataSize;
}

void prv_imGuiSetDataSizeWidget(void)
{
  int min = 0;
  int max = 10000; // Limit to 10,000 elements for this tier

  ImGui::Text("Data Size (max 10,000): ");

  /* Input field to set the data size */
  ImGui::InputInt("##DataSize", &bufferDataSize);

  /* Clamp the value within the specified range */
  bufferDataSize = std::clamp(bufferDataSize, min, max);
}

void prv_dataLabels(void)
{
  ImGui::Text("Channel Configuration:");


  int numChannels = getNumberOfChannels();

  // Resize the dataLabels vector if the number of channels has changed
  if (dataLabels.size() != numChannels)
  {
    dataLabels.resize(numChannels);
    // Initialize new labels with default names
    for (int i = 0; i < numChannels; ++i)
    {
      if (dataLabels[i].empty())
  {
        dataLabels[i] = "Channel " + std::to_string(i + 1);
      }
    }
  }

  // Note: numChannels is already validated in dataReceptionSettings
  // This is just a local variable for display purposes

  for (int i = 0; i < numChannels; ++i)
  {
    std::string label = "Channel " + std::to_string(i + 1);
    char buffer[256];

    // Safe string copy
    std::strncpy(buffer, dataLabels[i].c_str(), sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0'; // Ensure null-termination

    // Create a row with checkbox and input text
    ImGui::BeginGroup();
    
    // Checkbox for channel visibility with better label
    std::string checkboxLabel = "Show Individual Plot##Visible" + std::to_string(i);
    ImGui::Checkbox(checkboxLabel.c_str(), &channelVisibility[i]);
    
    // Input text for label on next line
    if (ImGui::InputText(label.c_str(), buffer, sizeof(buffer)))
    {
      dataLabels[i] = buffer;
      // Ensure label is never empty - use default if user clears it
      if (dataLabels[i].empty())
      {
        dataLabels[i] = "Channel " + std::to_string(i + 1);
      }
    }
    
    ImGui::EndGroup();
    
    // Add some spacing between channels
    if (i < numChannels - 1)
    {
      ImGui::Spacing();
    }
  }
}

void getDataLabels(std::vector<std::string> &labels)
{
  labels = dataLabels;
  
  // Ensure no empty labels are returned - provide defaults if needed
  for (size_t i = 0; i < labels.size(); ++i)
  {
    if (labels[i].empty())
    {
      labels[i] = "Channel " + std::to_string(i + 1);
    }
  }
}

/**
 * @brief Gets the visibility status of channels for individual plots
 * @param visibility Vector to store the visibility status of each channel
 */
void getChannelVisibility(std::vector<bool> &visibility)
{
  visibility.clear();
  int numChannels = getNumberOfChannels();
  for (int i = 0; i < numChannels && i < 3; ++i)
  {
    // Ensure we don't access beyond array bounds
    if (i < sizeof(channelVisibility) / sizeof(channelVisibility[0]))
    {
      visibility.push_back(channelVisibility[i]);
    }
    else
    {
      visibility.push_back(false); // Default to hidden for additional channels
    }
  }
}

void viewerSettings(void)
{
  if (ImGui::CollapsingHeader("Live View Settings",
                              ImGuiTreeNodeFlags_DefaultOpen))
  {
    prv_imGuiSetDataSizeWidget();

    prv_dataLabels();
  }
}
