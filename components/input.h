#pragma once
/** @file      input.h
 *  @brief     Header file for the input functions.
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

#include "../pch/pch.h"

namespace ncomponents
{
enum class EInputButton
{
  Left = 0,
  Right = 1,
  Middle = 2,
  None = 9
};

class Input
{
public:
  static EInputButton GetPressedButton(GLFWwindow *window)
  {
    EInputButton result = EInputButton::None;

    if (glfwGetMouseButton(window, 0) == GLFW_PRESS)
      return EInputButton::Left;
    else if (glfwGetMouseButton(window, 1) == GLFW_PRESS)
      return EInputButton::Right;
    else if (glfwGetMouseButton(window, 2) == GLFW_PRESS)
      return EInputButton::Middle;

    return EInputButton::None;
  }
};
} // namespace ncomponents
