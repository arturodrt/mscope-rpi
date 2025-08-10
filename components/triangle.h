#pragma once
/** @file      grid.h
 *  @brief     Header file for the grid functions.
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
#include "components.h"
#include "../render/renderBase.h"

namespace ncomponents
{
class Triangle : public Component
{

public:
  Triangle();
  virtual ~Triangle() = default;

  void update(nshaders::Shader *pShader) override {}

  void createBuffers(void);

  void deleteBuffers(void);

  void render(void);

  void bind(void);

  void unbind(void);

private:
  std::unique_ptr<nrender::VertexIndexBuffer> pRenderBufferMgr_m;
  std::vector<VertexHolder> mVertices;
  std::vector<unsigned int> mVertexIndices;
};
} // namespace ncomponents
