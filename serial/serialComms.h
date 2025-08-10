/** @file      serialComms.hpp
 *  @brief     Header file for Serial Communication functions.
 *  @author    arturodlrios
 *  @date      Created on 2024/02/29
 *
 *  This software is the exclusive property of Cortx and is provided
 *  under strict confidentiality. It is intended for use solely by authorized
 *  personnel of Cortx and is protected by intellectual property laws.
 *  Unauthorized use, reproduction, or distribution in whole or in part is
 * strictly prohibited.
 *
 *  COPYRIGHT NOTICE: 2025 Cortx, Montreal, QC. All rights reserved.
 */

#ifndef SERIAL_COMMS_H
#define SERIAL_COMMS_H

#include <vector>
#include "../Libraries/lib.h"
#include <string>
#include <cstdint>

extern std::vector<std::vector<float>> channelsData;
extern std::vector<float> xValues;

OrbCode_t openCOMPort(const std::string &comPortName, uint32_t baudRate,
                      uint8_t stopBits, uint8_t parity);

void closeCOMPort(void);

/**
 * @brief Starts a thread that continuously reads serial data until stopped.
 *
 * Sets a flag to indicate that the serial thread is running and enters a loop
 * to continuously read serial data until the thread is stopped.
 */
void startSerialThread(void);

/**
 * @brief Ends the serial thread by setting a flag to stop its execution.
 *
 * Sets the flag `threadRunning` to false, signaling the serial thread to
 * stop execution.
 */
void endSerialThread(void);

/**
 * @brief Reads serial data from the serial port.
 *
 * This function reads serial data from the serial port and processes it.
 * The received data is expected to be in a specific format where each message
 * starts with a '\r\n' sequence and ends with another '\r\n' sequence. The
 * function parses each received message and updates the provided string with
 * the parsed data.
 *
 * @return An OrbCode value indicating the outcome of the operation:
 *         - Success: Operation completed successfully.
 *         - ReadError: An error occurred while reading serial data.
 *
 */
OrbCode_t readSerialData(void);

#endif // SERIAL_COMMS_H
