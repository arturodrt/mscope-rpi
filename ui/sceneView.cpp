/** @file      sceneView.c
 *  @brief     Source file for the scene view functions.
 *  @author    arturodlr
 *  @date      Created on 2024/02/22
 *
 *  This software is the exclusive property of Cortx and is provided
 *  under strict confidentiality. It is intended for use solely by authorized
 *  personnel of Cortx and is protected by intellectual property laws.
 *  Unauthorized use, reproduction, or distribution in whole or in part is
 *  scrictly prohibited.
 *
 *  COPYRIGHT NOTICE: 2025 Cortx, Montreal, QC. All rights reserved.
 */

#include "sceneView.h"
#include "visualizer.h"
#include "settings.h"

namespace nui
{
void SceneView::render(void)
{
  plot();
  settings();
}

void SceneView::resize(int32_t width, int32_t height)
{
  size_m.x = width;
  size_m.y = height;

  pFrameBuffer_m->createBuffers((int32_t)size_m.x, (int32_t)size_m.y);
}

void SceneView::onMouseMove(double x, double y,
                            ncomponents::EInputButton button)
{
  // pCamera_m->onMouseMove(x, y, button);
}

void SceneView::onMouseWheel(double delta)
{
  // pCamera_m->onMouseWheel(delta);
}
} // namespace nui
