#pragma once
/** @file      openglBufferManagement.h
 *  @brief     Header file for the OpenGL buffer management functions.
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
#include "renderBase.h"

namespace nrender
{
class OpenGLFrameBuffer : public FrameBuffer
{
public:
  void createBuffers(int32_t width, int32_t height) override;

  void deleteBuffers(void) override;

  void bind(void) override;

  void unbind(void) override;

  uint32_t getTexture(void) override;
};

class OpenGLVertexIndexBuffer : public VertexIndexBuffer
{
public:
  OpenGLVertexIndexBuffer();
  virtual ~OpenGLVertexIndexBuffer() = default;

  void createBuffers(const std::vector<ncomponents::VertexHolder> &vertices,
                     const std::vector<unsigned int> &indices) override;

  void deleteBuffers(void) override;

  void bind(void) override;

  void unbind(void) override;

  void draw(int32_t indexCount) override;
};

} // namespace nrender
