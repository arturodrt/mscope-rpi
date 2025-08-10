/** @file      application.cpp
 *  @brief     Source file for the application functions.
 *  @author    arturodlrios
 *  @date      Created on 2024/02/27
 *
 *  This software is the exclusive property of Cortx and is provided
 *  under strict confidentiality. It is intended for use solely by authorized
 *  personnel of Cortx and is protected by intellectual property laws.
 *  Unauthorized use, reproduction, or distribution in whole or in part is
 * scrictly prohibited.
 *
 *  COPYRIGHT NOTICE: 2025 Cortx, Montreal, QC. All rights reserved.
 */

#include "application.h"
#include "../Libraries/lib.h"
#include "../serial/csvStorage.h"

Application::Application(const std::string &appName)
{
  OrbCode_t orbCode = Success;

  pWindow_m = std::make_unique<nwindow::GLWindow>();
  orbCode = pWindow_m->init(1024, 720, appName);
}

void Application::loop(void)
{
  const double targetFrameTime = 1.0 / 60.0; // Target 60 FPS
  double lastFrameTime = glfwGetTime();
  
  /* render loop */
  while (pWindow_m->isRunning())
  {
    double currentTime = glfwGetTime();
    double deltaTime = currentTime - lastFrameTime;
    
    // Limit frame rate to prevent excessive CPU usage
    if (deltaTime < targetFrameTime) {
      glfwWaitEventsTimeout(targetFrameTime - deltaTime);
    }
    
    pWindow_m->render();
    lastFrameTime = glfwGetTime();
  }
}

Application::~Application()
{
  /* Stop CSV recording if active when application closes */
  if (isCSVRecording())
  {
    stopCSVRecording();
  }
}
