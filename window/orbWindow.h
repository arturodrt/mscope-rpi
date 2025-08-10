#pragma once
/** @file      orbWindow.h
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

#include "../pch/pch.h"
#include "../window/window.h"
#include "../render/openglContext.h"
#include "../render/uiContext.h"
#include "../ui/sceneView.h"
#include "../render/uiContext.h"
#include "../render/openglContext.h"
#include "../render/openglBufferManagement.h"
#include "../shader/shaderUtil.h"

using namespace nrender;
using namespace nui;
using namespace ncomponents;
using namespace nshaders;

namespace nwindow
{
class GLWindow : public IWindow
{
public:
  GLWindow(void)
    : pWindow_m(nullptr)
    , isRunning_m(true)
  {
    pRenderContext_m = std::make_unique<OpenGLContext>();
    pUIContext_m = std::make_unique<UIContext>();
  }
  ~GLWindow(void);

  OrbCode_t init(uint16_t width, uint16_t height, const std::string &title);

  void render();

  void *pGetNativeWindow(void) override { return pWindow_m; }

  void setNativeWindow(void *pWindow) override
  {
    pWindow_m = (GLFWwindow *)pWindow;
  }

  void onClose(void) override;

  void onResize(int32_t width, int32_t height) override;

  void handleInput(void);

  void onScroll(double delta) override;

  void onKey(int key, int scanCode, int action, int mods) override;

  bool isRunning(void) { return isRunning_m; }

private:
  GLFWwindow *pWindow_m;

  /* Render contexts */
  std::unique_ptr<UIContext> pUIContext_m;

  std::unique_ptr<OpenGLContext> pRenderContext_m;

  /* UI components */
  std::unique_ptr<SceneView> pSceneView_m;

  bool isRunning_m;
};
} // namespace nwindow
