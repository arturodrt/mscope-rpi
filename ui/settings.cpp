/** @file      settings.cpp
 *  @brief     Source file for the settings functions.
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
#include <vector>
#include <string>
#include "../serial/serialComms.h"
#include "serialSettings.h"
#include "viewerSettings.h"
#include "dataReceptionSettings.h"
#include "generalSettings.h"
#include "csvRecordingSettings.h"

void settings(void)
{
  // Get the main dockspace ID
  ImGuiID dockspaceId = ImGui::GetID("InvisibleWindowDockSpace");
  
  // Set the Settings window to dock into the main dockspace
  ImGui::SetNextWindowDockID(dockspaceId, ImGuiCond_FirstUseEver);
  ImGui::SetNextWindowSize(ImVec2(350, 600), ImGuiCond_FirstUseEver);
  
  ImGui::Begin("Settings");

  /* Container for serial communication settings */
  ImGui::Separator();

  generalSettings();

  ImGui::Separator();

  serialComSettings();

  ImGui::Separator();

  dataReceptionSettings();

  ImGui::Separator();

  csvRecordingSettings();

  ImGui::Separator();

  viewerSettings();

  ImGui::Separator();

  ImGui::End();
}
