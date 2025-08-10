#pragma once
/** @file      csvRecordingSettings.h
 *  @brief     Header file for the CSV recording settings functions.
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

#include <string>
#include <vector>

/**
 * @brief Renders the CSV recording settings UI
 * 
 * This function displays controls for:
 * - Starting/stopping CSV recording
 * - Setting the output filename
 * - Configuring channel names
 * - Displaying recording status
 */
void csvRecordingSettings(void);

/**
 * @brief Gets the current CSV filename from user input
 * @return The filename entered by the user
 */
std::string getCSVFilename(void);

/**
 * @brief Gets the channel names for CSV headers
 * @return Vector of channel names
 */
std::vector<std::string> getChannelNames(void); 