/** @file      imguiCustomThemes.h
 *  @brief     Header file for the custom imgui themes functions.
 *  @author    arturodlr
 *  @date      Created on 2024/05/20
 *
 *  This software is the exclusive property of Cortx and is provided
 *  under strict confidentiality. It is intended for use solely by authorized
 *  personnel of Cortx and is protected by intellectual property laws.
 *  Unauthorized use, reproduction, or distribution in whole or in part is
 *  scrictly prohibited.
 *
 *  COPYRIGHT NOTICE: 2025 Cortx, Montreal, QC. All rights reserved.
 */

/* Includes
 * ----------------------------------------------------------------------------------
 */
#include "../backends/imgui.h"
#include "../backends/imgui_impl_glfw.h"
#include "../backends/imgui_impl_opengl3.h"

/**
 * @brief Sets the ImGui style to a moonshine theme.
 *
 * This function modifies the provided ImGuiStyle object to apply a moonshine
 * theme.
 *
 * @param style Reference to the ImGuiStyle object to be modified.
 */
void SetImGuiStyleMoonshine(ImGuiStyle &style);

/**
 * @brief Sets the ImGui style to the embraceTheDarkness theme.
 *
 * This function modifies the provided ImGuiStyle object to apply
 * embraceTheDarkness theme.
 *
 * @param style Reference to the ImGuiStyle object to be modified.
 */
void SetImGuiStyleEmbraceTheDarkness(ImGuiStyle &style);

/**
 * @brief Sets the ImGui style to the mscope theme.
 *
 * This function modifies the provided ImGuiStyle object to apply mscope
 * theme.
 *
 * @param style Reference to the ImGuiStyle object to be modified.
 */
void SetImGuiStyleMscopeDark(ImGuiStyle &style);

/**
 * @brief Sets the ImGui style to the mscope theme light.
 *
 * This function modifies the provided ImGuiStyle object to apply mscope
 * theme.
 *
 * @param style Reference to the ImGuiStyle object to be modified.
 */
void SetImGuiStyleMscopeLight(ImGuiStyle &style);
