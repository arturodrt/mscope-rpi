/** @file      graph.c
 *  @brief     Source file for the graph functions.
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

/* Includes
 * ----------------------------------------------------------------------------------
 */
#include "graph.h"
#include "../render/openglBufferManagement.h"

/* Namespaces
 * --------------------------------------------------------------------------------
 */
namespace ncomponents
{

Graph::Graph()
{
  pRenderBufferMgr_m = std::make_unique<nrender::OpenGLVertexIndexBuffer>();

  createBuffers();
}

void Graph::createBuffers(void)
{
  pRenderBufferMgr_m->createBuffers(mVertices, mVertexIndices);
}

void Graph::deleteBuffers()
{
  pRenderBufferMgr_m->deleteBuffers();
}

void Graph::bind()
{
  pRenderBufferMgr_m->bind();
}

void Graph::unbind()
{
  pRenderBufferMgr_m->unbind();
}

void Graph::render()
{
  pRenderBufferMgr_m->draw((int)mVertexIndices.size());
}
} // namespace ncomponents
/* -------------------------------------------------------------------------------------------
 */
