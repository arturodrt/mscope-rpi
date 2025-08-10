/** @file      generalSettings.cpp
 *  @brief     Source file for the general settings functions.
 *  @author    arturodlrios
 *  @date      Created on 2024/08/04
 *
 *  This software is the exclusive property of Cortx and is provided
 *  under strict confidentiality. It is intended for use solely by authorized
 *  personnel of Cortx and is protected by intellectual property laws.
 *  Unauthorized use, reproduction, or distribution in whole or in part is
 *  scrictly prohibited.
 *
 *  COPYRIGHT NOTICE: 2025 Cortx, Montreal, QC. All rights reserved.
 */

#include "../backends/imgui.h"
#include "../backends/implot.h"
#include "generalSettings.h"
#include "IconsFontAwesome5.h" // Assuming you use FontAwesome icons
#include "../backends/imguiCustomThemes.h"

bool isThemeDark = true;

void prv_themeSelection(void)
{
  ImVec2 contentSize = ImGui::GetContentRegionAvail();
  float buttonSpacing = ImGui::GetStyle().ItemSpacing.x;
  float extraSpace = 10.0f;
  float buttonWidth = (contentSize.x - buttonSpacing) / 2.0f;

  ImGuiStyle &style = ImGui::GetStyle();

  ImGui::Text("Application Theme: ");

  ImGui::BeginGroup();

  if (ImGui::Button(ICON_FA_SUN " Light Theme", ImVec2(buttonWidth, 0)))
  {
    SetImGuiStyleMscopeLight(style);
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    isThemeDark = false;
  }

  ImGui::SameLine(0, extraSpace);

  if (ImGui::Button(ICON_FA_MOON " Dark Theme", ImVec2(buttonWidth, 0)))
  {
    SetImGuiStyleMscopeDark(style);
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    isThemeDark = true;
  }

  ImGui::EndGroup();
}

bool isThemeDarkSelected(void)
{
  return isThemeDark;
}

void generalSettings(void)
{
  if (ImGui::CollapsingHeader("General Settings",
                              ImGuiTreeNodeFlags_DefaultOpen))
  {
    prv_themeSelection();
  }
}
