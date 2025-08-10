/** @file      orbWindow.cpp
 *  @brief     Source file for the main window functions.
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

#include "orbWindow.h"
#include "../components/input.h"

namespace nwindow
{
OrbCode_t GLWindow::init(uint16_t width, uint16_t height,
                         const std::string &title)
{
  OrbCode_t orbCode = Success;

  width_m = width;
  height_m = height;
  windowTitle_m = title;

  orbCode = pRenderContext_m->init(this);

  if (orbCode != Success)
  {
    pRenderContext_m->end();
  }

  orbCode = pUIContext_m->init(this);

  if (orbCode != Success)
  {
    pUIContext_m->end();
  }

  pSceneView_m = std::make_unique<SceneView>();

  return orbCode;
}

GLWindow::~GLWindow(void)
{
  pRenderContext_m->end();
  pUIContext_m->end();
}

void GLWindow::onClose(void)
{
  isRunning_m = false;
}

void GLWindow::render(void)
{
  /* Clear the view */
  pRenderContext_m->preRender();

  /* Initialize UI components */
  pUIContext_m->preRender();

  /* render scene to framebuffer and add it to scene view */
  pSceneView_m->render();

  /* Render the UI */
  pUIContext_m->postRender();

  /* Render end, swap buffers */
  pRenderContext_m->postRender();

  handleInput();
}

void GLWindow::onResize(int32_t width, int32_t height)
{
  width_m = width;
  height_m = height;

  pSceneView_m->resize(width_m, height_m);
  render();
}

void GLWindow::onScroll(double delta)
{
  pSceneView_m->onMouseWheel(delta);
}

void GLWindow::onKey(int key, int scanCode, int action, int mods)
{
  if (action == GLFW_PRESS)
  {
    /* TODO */
  }
}

void GLWindow::handleInput(void)
{
  // TODO: move this and camera to scene UI component?

  if (glfwGetKey(pWindow_m, GLFW_KEY_W) == GLFW_PRESS)
  {
    pSceneView_m->onMouseWheel(-0.4f);
  }

  if (glfwGetKey(pWindow_m, GLFW_KEY_S) == GLFW_PRESS)
  {
    pSceneView_m->onMouseWheel(0.4f);
  }

  double x, y;
  glfwGetCursorPos(pWindow_m, &x, &y);

  pSceneView_m->onMouseMove(x, y, Input::GetPressedButton(pWindow_m));
}
} // namespace nwindow
