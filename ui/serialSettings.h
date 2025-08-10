#pragma once
/** @file      serialSettings.h
 *  @brief     Header file for the serial settings functions.
 *  @author    arturodlrios
 *  @date      Created on 2024/07/06
 *
 *  This software is the exclusive property of Cortx and is provided
 *  under strict confidentiality. It is intended for use solely by authorized
 *  personnel of Cortx and is protected by intellectual property laws.
 *  Unauthorized use, reproduction, or distribution in whole or in part is
 *  scrictly prohibited.
 *
 *  COPYRIGHT NOTICE: 2025 Cortx, Montreal, QC. All rights reserved.
 */

/**
 * @brief Indicates that an error has occurred during serial data readings.
 *
 * This function is called when errors are encountered during serial data
 * readings.
 *
 * @return void
 */
void serialReadingsError(void);

/**
 * @brief Checks if the serial port is opened.
 *
 * This function checks whether the serial communication port is currently
 * opened.
 *
 * @return true if the serial port is opened, false otherwise.
 */
bool isSerialPortOpened(void);

/**
 * @brief Configures and manages serial communication settings.
 *
 * This function sets up parameters such as baud rate, parity, and stop bits
 * for serial communication via a GUI. It includes options to configure
 * the port if it's not already open and manages the opened port otherwise.
 *
 */
void serialComSettings(void);
