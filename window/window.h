#pragma once
/** @file      window.h
 *  @brief     Header file for the window functions.
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

namespace nwindow
{
class IWindow
{
public:
  IWindow()
    : width_m(0)
    , height_m(0)
    , windowTitle_m("")
  {
  }
  virtual void *pGetNativeWindow(void) = 0;

  virtual void setNativeWindow(void *pWindow) = 0;

  virtual void onClose(void) = 0;

  virtual void onResize(int32_t width, int32_t height) = 0;

  virtual void onScroll(double delta) = 0;

  virtual void onKey(int key, int scanCode, int action, int mods) = 0;

  uint16_t width_m = 0;
  uint16_t height_m = 0;
  std::string windowTitle_m;
};
} // namespace nwindow
