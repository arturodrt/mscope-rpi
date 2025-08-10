#pragma once
/** @file      renderBase.h
 *  @brief     Header file for the render base functions.
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

#include "../window/window.h"
#include "../components/vertexHolder.h"

namespace nrender
{
class RenderContext
{
public:
  RenderContext()
    : pWindow_m(nullptr)
  {
  }

  virtual OrbCode_t init(nwindow::IWindow *pWindow)
  {
    pWindow_m = pWindow;
    return Success;
  }

  virtual void preRender(void) = 0;

  virtual void postRender(void) = 0;

  virtual void end(void) = 0;

protected:
  nwindow::IWindow *pWindow_m;
};

class FrameBuffer
{
public:
  FrameBuffer()
    : FBO_m{0}
    , depthId_m{0}
  {
  }

  virtual void createBuffers(int32_t width, int32_t height) = 0;

  virtual void deleteBuffers(void) = 0;

  virtual void bind(void) = 0;

  virtual void unbind(void) = 0;

  virtual uint32_t getTexture(void) = 0;

protected:
  uint32_t FBO_m = 0;
  uint32_t texId_m = 0;
  uint32_t depthId_m = 0;
  int32_t width_m = 0;
  int32_t height_m = 0;
};

class VertexIndexBuffer
{
public:
  VertexIndexBuffer(void)
    : glVBO_m{0}
    , glVAO_m{0}
    , glIBO_m{0}
  {
  }
  virtual ~VertexIndexBuffer() = default;

  virtual void
  createBuffers(const std::vector<ncomponents::VertexHolder> &vertices,
                const std::vector<unsigned int> &indices)
      = 0;

  virtual void deleteBuffers(void) = 0;

  virtual void bind(void) = 0;

  virtual void unbind(void) = 0;

  virtual void draw(int32_t indexCount) = 0;

protected:
  GLuint glVBO_m;
  GLuint glVAO_m;
  GLuint glIBO_m;
};

} // namespace nrender
