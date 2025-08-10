#pragma once
/** @file      vertexHolder.h
 *  @brief     Header file for the render vertex holder functions.
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
class VertexHolder
{

public:
  VertexHolder()
    : pos_m()
    , normal_m()
  {
  }

  /* Initialize by string to be tokenized */
  /* TODO: Better handle outside of this class */
  VertexHolder(const std::vector<std::string> tokens) {}

  VertexHolder(const glm::vec3 &pos, const glm::vec3 &normal)
    : pos_m(pos)
    , normal_m(normal)
  {
  }

  ~VertexHolder() = default;

  glm::vec3 pos_m;

  glm::vec3 normal_m;
};
} // namespace ncomponents
