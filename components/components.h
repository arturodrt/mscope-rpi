#pragma once
/** @file      components.h
 *  @brief     Header file for the components functions.
 *  @author    arturodlrios
 *  @date      Created on 2024/03/29
 *
 *  This software is the exclusive property of Cortx and is provided
 *  under strict confidentiality. It is intended for use solely by authorized
 *  personnel of Cortx and is protected by intellectual property laws.
 *  Unauthorized use, reproduction, or distribution in whole or in part is
 *  scrictly prohibited.
 *
 *  COPYRIGHT NOTICE: 2025 Cortx, Montreal, QC. All rights reserved.
 */

#include "../shader/shaderUtil.h"

namespace ncomponents
{
class Component
{
public:
  virtual void update(nshaders::Shader *pShader) = 0;
};
} // namespace ncomponents
