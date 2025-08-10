/** @file      serialTerminal.h
 *  @brief     Header file for the serial monitor functions.
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
#include "../Libraries/lib.h"

/**
 * @brief Updates and displays a serial terminal interface using ImGui for
 * real-time serial data logging and visualization.
 *
 * This function orchestrates the updating and display of a serial terminal
 * interface using ImGui. It first logs the latest float data to a serial data
 * buffer stream and then displays this data in a scrolling terminal window. The
 * ImGui-based UI provides real-time visualization of serial data for monitoring
 * purposes.
 */
void serialTerminal(void);

/**
 * @brief Checks whether data reception is currently paused.
 *
 * This function returns the current status of data reception. If the data
 * reception is paused, it returns true; otherwise, it returns false.
 *
 * @return true if data reception is paused, false otherwise.
 */
bool isDataReceptionPaused(void);
