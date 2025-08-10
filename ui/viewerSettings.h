#pragma once
/** @file      viewerSettings.h
 *  @brief     Header file for the viewer settings functions.
 *  @author    arturodlrios
 *  @date      Created on 2024/03/29
 *
 *  This software is the exclusive property of Cortx and is provided
 *  under strict confidentiality. It is intended for use solely by authorized
 *  personnel of Cortx and is protected by intellectual property laws.
 *  Unauthorized use, reproduction, or distribution in whole or in part is
 *  scrictly prohibited.
 *
 *  COPYRIGHT NOTICE: 2025 Cortx, Montreal, QC. All rights reserved.
 */

#include <string>
#include <vector>

/**
 * @brief Displays viewer settings using ImGui, including live view settings.
 *
 * This function creates an ImGui interface for viewer settings. It includes a
 * collapsing header titled "Live View Settings", which is initially open
 * (`ImGuiTreeNodeFlags_DefaultOpen`). Within this header, it displays widgets
 * and settings related to live viewing. Currently, it includes a widget
 * provided by `prv_imGuiSetDataSizeWidget()` to set the data size for the
 * viewer buffer.
 */
void viewerSettings(void);

/**
 * @brief Retrieves the current size of the viewer data buffer.
 *
 * This function returns the current size of the viewer data buffer, which is
 * represented by the variable `bufferDataSize`. The size indicates how many
 * elements or data points are currently stored in the buffer.
 *
 * @return The current size of the viewer data buffer.
 */
int viewerDataSize(void);

/**
 * @brief Retrieves the current data labels and stores them in the provided
 * pointers.
 *
 * This function sets the values pointed to by `label1`, `label2`, and `label3`
 * to the current names of the data series. If a pointer is null, the
 * corresponding label will not be modified.
 *
 * @param[in, out] labels Pointer to a std::string where the data labels will be
 * stored.
 *
 * @note If any of the provided pointers are null, the function will skip
 * updating that particular label. Ensure that valid pointers are provided to
 * avoid unintended behavior.
 */
void getDataLabels(std::vector<std::string> &labels);

/**
 * @brief Gets the visibility status of channels for individual plots
 * @param visibility Vector to store the visibility status of each channel
 */
void getChannelVisibility(std::vector<bool> &visibility);
