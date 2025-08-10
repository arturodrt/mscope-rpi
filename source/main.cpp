/** @file      main.cpp
 *  @brief     Entry Point.
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

#include "../pch/pch.h"
#include "../app/application.h"
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include "../serial/serialComms.h"
#include "../ui/visualizer.h"
/* Entry Point
 * -------------------------------------------------------------------------------
 */

int main(void)
{
  std::thread serialThread(startSerialThread);

  auto pApp = std::make_unique<Application>("μscope");

  pApp->loop();

  endSerialThread();

  if (serialThread.joinable())
  {
    serialThread.join();
  }

  return 0;
}
