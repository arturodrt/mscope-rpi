#pragma once
/** @file      application.h
 *  @brief     Header file for the application functions.
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

#include "../window/orbWindow.h"

class Application
{
public:
  Application(const std::string &appName);
  ~Application();

  static Application &Instance(void) { return *pInstance; }

  void loop();

private:
  static Application *pInstance;

  std::unique_ptr<nwindow::GLWindow> pWindow_m;
};
