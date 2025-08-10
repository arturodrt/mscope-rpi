#pragma once
/** @file      lib.h
 *  @brief     Cortx library header.
 *  @author    arturodlrios
 *  @date      Created on 2024/02/27
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
 * @brief Error management codes
 *
 */
typedef enum
{
  Error = 0,
  Success,
  ReadError,
  OpenError,
  PortStateError,
  InitError,
  NotAvailable,
  WrongBaudRate,
  TimeoutError,
  DataReceived,
  InvalidData,
  ConfigError
} OrbCode_t;
