/** @file      Triangle.c
 *  @brief     Source file for the Triangle functions.
 *  @author    arturodlr
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

#include "triangle.h"
#include "../render/openglBufferManagement.h"

namespace ncomponents
{
float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};

Triangle::Triangle()
{
  pRenderBufferMgr_m = std::make_unique<nrender::OpenGLVertexIndexBuffer>();
  mVertices = {
      VertexHolder(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
      VertexHolder(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
      VertexHolder(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f))};

  mVertexIndices = {0, 1, 2};

  createBuffers();
}

void Triangle::createBuffers(void)
{
  pRenderBufferMgr_m->createBuffers(mVertices, mVertexIndices);
}

void Triangle::deleteBuffers()
{
  pRenderBufferMgr_m->deleteBuffers();
}

void Triangle::bind()
{
  pRenderBufferMgr_m->bind();
}

void Triangle::unbind()
{
  pRenderBufferMgr_m->unbind();
}

void Triangle::render()
{
  pRenderBufferMgr_m->draw((int)mVertexIndices.size());
}
} // namespace ncomponents
