/** @file      openglContext.cpp
 *  @brief     OpenGL context management for Raspberry Pi
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
#include "openglContext.h"

namespace nrender
{
static uint16_t usWindowWidth_m;
static uint16_t usWindowHeight_m;

static void vOnWindowCloseCallback(GLFWwindow *pGLWindow)
{
  nwindow::IWindow *pWindow
      = static_cast<nwindow::IWindow *>(glfwGetWindowUserPointer(pGLWindow));
  pWindow->onClose();
}

static void vOnWindowSizeCallback(GLFWwindow *glpWindow, int width, int height)
{
  auto pWindow
      = static_cast<nwindow::IWindow *>(glfwGetWindowUserPointer(glpWindow));
  pWindow->onResize(width, height);
  usWindowWidth_m = width;
  usWindowHeight_m = height;
}

static void onKeyCallback(GLFWwindow *glpWindow, int key, int scanCode,
                          int action, int mods)
{
  auto pWindow
      = static_cast<nwindow::IWindow *>(glfwGetWindowUserPointer(glpWindow));
  pWindow->onKey(key, scanCode, action, mods);
}

static void onScrollCallback(GLFWwindow *glpWindow, double dXOffset,
                             double dYOffset)
{
  auto pWindow
      = static_cast<nwindow::IWindow *>(glfwGetWindowUserPointer(glpWindow));
  pWindow->onScroll(dYOffset);
}

void OpenGLContext::getWindowSize(uint16_t &ucWidth, uint16_t &ucHeight)
{
  ucWidth = usWindowWidth_m;
  ucHeight = usWindowHeight_m;
}

OrbCode_t OpenGLContext::init(nwindow::IWindow *pWindow)
{
  RenderContext::init(pWindow);

  /* initialize GLFW */
  if (!glfwInit())
  {
    fprintf(stderr, "Error: GLFW Window couldn't be initialized\n");
    return InitError;
  }
  
  /* configure GLFW for Raspberry Pi - Use OpenGL ES 2.0 */
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);

  /* Create a window object and store it as a window pointer
  so that it can be used in callback functions */

  usWindowWidth_m = pWindow->width_m;
  usWindowHeight_m = pWindow->height_m;

  auto *pGLWindow
      = glfwCreateWindow(pWindow->width_m, pWindow->height_m,
                         pWindow->windowTitle_m.c_str(), nullptr, nullptr);

  pWindow->setNativeWindow(pGLWindow);

  if (!pGLWindow)
  {
    fprintf(stderr, "Error: GLFW Window couldn't be created\n");
    return InitError;
  }

  glfwSetWindowUserPointer(pGLWindow, pWindow);
  glfwSetWindowCloseCallback(pGLWindow, vOnWindowCloseCallback);
  glfwSetWindowSizeCallback(pGLWindow, vOnWindowSizeCallback);
  glfwSetKeyCallback(pGLWindow, onKeyCallback);
  glfwSetScrollCallback(pGLWindow, onScrollCallback);

  /*  make the context of our window the main context on the current thread */
  glfwMakeContextCurrent(pGLWindow);

  /* For Raspberry Pi with OpenGL ES, we don't need GLEW */
  /* OpenGL ES functions are available directly */
  fprintf(stderr, "Using OpenGL ES 2.0 on Raspberry Pi\n");

  /* Enable blending for transparency */
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  /* Set the viewport */
  glViewport(0, 0, usWindowWidth_m, usWindowHeight_m);

  return Success;
}

void OpenGLContext::preRender(void)
{
  glViewport(0, 0, pWindow_m->width_m, pWindow_m->height_m);
  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLContext::postRender(void)
{
  glfwPollEvents();
  glfwSwapBuffers((GLFWwindow *)pWindow_m->pGetNativeWindow());
}

void OpenGLContext::end(void)
{
  glfwDestroyWindow((GLFWwindow *)pWindow_m->pGetNativeWindow());
  glfwTerminate();
}

} /* namespace nrender */
