#pragma once
/** @file      sceneView.h
 *  @brief     Header file for the scene view functions.
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

#include "../render/openglBufferManagement.h"
#include "../shader/shaderUtil.h"
#include "../components/input.h"
#include "../components/triangle.h"

namespace nui
{
class SceneView
{
public:
  SceneView()
    : pFrameBuffer_m(nullptr)
    , pShader_m(nullptr)
    , pTriangle_m(nullptr)
    , size_m(595, 842)
  {
    pFrameBuffer_m = std::make_unique<nrender::OpenGLFrameBuffer>();
    pFrameBuffer_m->createBuffers(595, 842);
    pShader_m = std::make_unique<nshaders::Shader>();
#ifdef PLATFORM_RASPBERRY_PI
    pShader_m->load("shader/trivs_rpi.shader", "shader/trifs_rpi.shader");
#else
    pShader_m->load("shader/trivs.shader", "shader/trifs.shader");
#endif
    pTriangle_m = std::make_unique<ncomponents::Triangle>();
  }

  ~SceneView() { pShader_m->unload(); }

  void render(void);

  void resize(int32_t width, int32_t height);

  void onMouseMove(double x, double y, ncomponents::EInputButton button);

  void onMouseWheel(double delta);

private:
  std::unique_ptr<nrender::OpenGLFrameBuffer> pFrameBuffer_m;
  std::unique_ptr<nshaders::Shader> pShader_m;
  std::shared_ptr<ncomponents::Triangle> pTriangle_m;
  glm::vec2 size_m;
};
} // namespace nui
