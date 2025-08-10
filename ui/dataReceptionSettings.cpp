/** @file      dataReceptionSettings.c
 *  @brief     Source file for the data reception settings functions.
 *  @author    arturodlrios
 *  @date      Created on 2024/07/24
 *
 *  This software is the exclusive property of Cortx and is provided
 *  under strict confidentiality. It is intended for use solely by authorized
 *  personnel of Cortx and is protected by intellectual property laws.
 *  Unauthorized use, reproduction, or distribution in whole or in part is
 *  scrictly prohibited.
 *
 *  COPYRIGHT NOTICE: 2025 Cortx, Montreal, QC. All rights reserved.
 */

#include "../Libraries/lib.h"
#include "../backends/imgui.h"
#include "../backends/implot.h"
#include "settings.h"
#include "../pch/pch.h"

static int numChannels = 0;

void prv_channelSelection(void)
{
  ImGui::Text("Number of channels:");

  /* Input field to set the data size */
  int oldValue = numChannels;
  bool changed = ImGui::InputInt("Channels", &numChannels);
  
  // Only clamp if the value is outside the valid range AND the user actually changed it
  if (changed && numChannels > 3)
  {
    numChannels = 3;
  }
  else if (changed && numChannels < 0)
  {
    numChannels = 0;
  }
}

int getNumberOfChannels(void)
{
  return numChannels;
}

void dataReceptionSettings(void)
{
  if (ImGui::CollapsingHeader("Data Reception Settings",
                              ImGuiTreeNodeFlags_DefaultOpen))
  {
    prv_channelSelection();
  }
}
