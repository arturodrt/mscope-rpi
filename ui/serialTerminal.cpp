/** @file      serialTerminal.cpp
 *  @brief     Source file for the serial monitor functions.
 *  @author    arturodlr
 *  @date      Created on 2024/07/07
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
#include "serialTerminal.h"
#include "../Libraries/lib.h"
#include "../serial/serialComms.h"
#include <iomanip>
#include <filesystem>
#include "../pch/pch.h"
#include "../dependencies/include/stb/stb_image.h" // For image loading (make sure you include this in your project)
#include "IconsFontAwesome5.h"

static std::stringstream
    serialDataBufferStream; /* Using stringstream for efficient string
                               operations */
const size_t maxSerialDataBufferSize = 20000; /* Example size limit */
bool pauseIncomingData = false;

/**
 * @brief Trims the serial data buffer stream if its size exceeds the maximum
 * allowed size.
 *
 * If the current content size of the serial data buffer stream exceeds the
 * maximum size limit
 * (`maxSerialDataBufferSize`), this function trims the content to ensure it
 * does not exceed this limit. It adjusts the content by removing excess
 * characters from the beginning, preserving the last complete line of data.
 */
void prv_trimSerialDataBufferIfNeeded(void);

/**
 * @brief Logs the latest float data from three float vectors to a serial data
 * buffer stream.
 *
 * Logs the last elements from three float vectors (`floatVector1`,
 * `floatVector2`, `floatVector3`) to a serial data buffer stream
 * (`serialDataBufferStream`). Each float value is formatted with fixed
 * precision of 4 decimal places before being appended to the stream. After
 * logging the data, it trims the serial data buffer if its size exceeds a
 * maximum limit.
 */
void prv_LogFloatDataWithImGui(void);

/**
 * @brief Displays a serial terminal window using ImGui for real-time serial
 * data visualization.
 *
 * This function creates an ImGui window titled "Serial Terminal" and displays
 * the contents of the `serialDataBufferStream`. It formats the contents to
 * ensure proper scrolling within the ImGui window. If the scroll reaches the
 * bottom, it automatically scrolls to show the latest data. The window includes
 * a scrolling region to handle large amounts of data.
 */
void prv_imGuiSerialTerminal(void);

void prv_trimSerialDataBufferIfNeeded(void)
{
  /* Get the current content of the stream */
  std::string currentContent = serialDataBufferStream.str();

  /* Check if current content size exceeds the maximum size limit */
  if (currentContent.size() > maxSerialDataBufferSize)
  {
    /* Calculate how much to trim */
    size_t excessSize = currentContent.size() - maxSerialDataBufferSize;

    /* Find the position of the last '\n' within the excess content */
    size_t lastNewlinePos = currentContent.rfind('\n', excessSize);

    /* If '\n' is found within the excess content, adjust excessSize to trim up
     * to '\n' */
    if (lastNewlinePos != std::string::npos)
    {
      excessSize = lastNewlinePos + 1; /* Include the '\n' itself */
    }

    /* Remove excess characters from the beginning of the content */
    currentContent = currentContent.substr(excessSize);

    /* Clear the stream and update with the trimmed content */
    serialDataBufferStream.str("");
    serialDataBufferStream.clear(); /* Clear any error flags */
    serialDataBufferStream << currentContent;
  }
}

void prv_LogFloatDataWithImGui(void)
{
  const int numChannels = channelsData.size();

  serialDataBufferStream
      << std::fixed
      << std::setprecision(
             4); /* Optional: Format floats with fixed precision */

  if (numChannels > 0)
  {
    for (int i = 0; i < numChannels; ++i)
    {
      // Check if the current channel data is not empty
      if (i < channelsData.size() && !channelsData[i].empty())
      {

        serialDataBufferStream << channelsData[i].back() << " ";
      }
    }

    serialDataBufferStream << std::endl;

    prv_trimSerialDataBufferIfNeeded();
  }
}

void prv_imGuiSerialTerminal(void)
{
  // Get the main dockspace ID
  ImGuiID dockspaceId = ImGui::GetID("InvisibleWindowDockSpace");
  
  // Set the Serial Terminal window to dock into the main dockspace
  ImGui::SetNextWindowDockID(dockspaceId, ImGuiCond_FirstUseEver);
  ImGui::SetNextWindowSize(ImVec2(500, 300), ImGuiCond_FirstUseEver);
  
  ImGui::Begin("Serial Terminal");

  ImVec2 contentSize = ImGui::GetContentRegionAvail();
  float buttonSpacing = ImGui::GetStyle().ItemSpacing.x;
  float extraSpace = 10.0f;

  float buttonWidth = (contentSize.x - buttonSpacing) / 2.0f;

  ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

  ImGui::BeginGroup();

  if (ImGui::Button(ICON_FA_PLAY " Play", ImVec2(buttonWidth, 0)))
  {
    pauseIncomingData = false;
  }

  ImGui::SameLine(0, extraSpace);

  if (ImGui::Button(ICON_FA_STOP " Stop", ImVec2(buttonWidth, 0)))
  {
    pauseIncomingData = true;
  }

  ImGui::EndGroup();

  ImGui::PopStyleVar();

  ImGui::Separator();
  ImGui::BeginChild("ScrollingRegion",
                    ImVec2(0, -ImGui::GetTextLineHeightWithSpacing()), false,
                    ImGuiWindowFlags_HorizontalScrollbar);

  /* Display contents from the stringstream buffer */
  ImGui::TextUnformatted(serialDataBufferStream.str().c_str());

  if (true && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
    ImGui::SetScrollHereY(1.0f);

  ImGui::EndChild();

  ImGui::End();
}

bool isDataReceptionPaused(void)
{
  return pauseIncomingData;
}

void serialTerminal(void)
{
  prv_LogFloatDataWithImGui();
  prv_imGuiSerialTerminal();
}
