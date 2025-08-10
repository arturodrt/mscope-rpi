#pragma once
/** @file      uiContext.h
 *  @brief     Header file for the UI Context functions.
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

#include "renderBase.h"

namespace nrender
{
class UIContext : public RenderContext
{

public:
  OrbCode_t init(nwindow::IWindow *pWindow) override;

  void preRender(void) override;

  void postRender(void) override;

  void end(void) override;
};
} // namespace nrender
