/** @file      openglBufferManagement.cpp
 *  @brief     Source file for the OpenGL buffer management functions.
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

#include "openglBufferManagement.h"

namespace nrender
{
OpenGLVertexIndexBuffer::OpenGLVertexIndexBuffer()
  : VertexIndexBuffer()
{
  /* Constructor implementation */
}
void OpenGLFrameBuffer::bind(void)
{
  glBindFramebuffer(GL_FRAMEBUFFER, FBO_m);
  glViewport(0, 0, width_m, height_m);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLFrameBuffer::unbind(void)
{
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGLFrameBuffer::createBuffers(int32_t width, int32_t height)
{
  width_m = width;
  height_m = height;

  if (FBO_m)
  {
    deleteBuffers();
  }

  // Generate and bind the framebuffer
  glGenFramebuffers(1, &FBO_m);
  glBindFramebuffer(GL_FRAMEBUFFER, FBO_m);

  // Generate and bind the color texture
  glGenTextures(1, &texId_m);
  glBindTexture(GL_TEXTURE_2D, texId_m);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_m, height_m, 0, GL_RGB,
               GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
#ifndef PLATFORM_RASPBERRY_PI
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
#endif
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                         texId_m, 0);

  // Generate and bind the depth-stencil texture
  glGenTextures(1, &depthId_m);
  glBindTexture(GL_TEXTURE_2D, depthId_m);
#ifdef PLATFORM_RASPBERRY_PI
  // OpenGL ES compatible depth texture
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width_m, height_m, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT, NULL);
#else
  glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, width_m, height_m);
#endif
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
#ifndef PLATFORM_RASPBERRY_PI
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
#endif
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
#ifdef PLATFORM_RASPBERRY_PI
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthId_m, 0);
#else
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                         GL_TEXTURE_2D, depthId_m, 0);
#endif

#ifndef PLATFORM_RASPBERRY_PI
  // Specify the list of draw buffers (only one in this case) - not available in OpenGL ES
  GLenum buffers[1] = {GL_COLOR_ATTACHMENT0};
  glDrawBuffers(1, buffers);
#endif

  // Check framebuffer completeness
  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
  {
    std::cerr << "Framebuffer is not complete!" << std::endl;
  }

  // Unbind the framebuffer
  unbind();
}

void OpenGLFrameBuffer::deleteBuffers(void)
{
  if (FBO_m)
  {
    glDeleteFramebuffers(1, &FBO_m);
    FBO_m = 0;
  }

  if (texId_m)
  {
    glDeleteTextures(1, &texId_m);
    texId_m = 0;
  }

  if (depthId_m)
  {
    glDeleteTextures(1, &depthId_m);
    depthId_m = 0;
  }
}

uint32_t OpenGLFrameBuffer::getTexture(void)
{
  return texId_m;
}

void OpenGLVertexIndexBuffer::createBuffers(
    const std::vector<ncomponents::VertexHolder> &vertices,
    const std::vector<unsigned int> &indices)
{
#ifndef PLATFORM_RASPBERRY_PI
  // VAOs are not available in OpenGL ES 2.0
  glGenVertexArrays(1, &glVAO_m);
#endif

  glGenBuffers(1, &glIBO_m);
  glGenBuffers(1, &glVBO_m);

#ifndef PLATFORM_RASPBERRY_PI
  glBindVertexArray(glVAO_m);
#endif

  glBindBuffer(GL_ARRAY_BUFFER, glVBO_m);
  glBufferData(GL_ARRAY_BUFFER,
               vertices.size() * sizeof(ncomponents::VertexHolder),
               vertices.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glIBO_m);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
               indices.data(), GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                        sizeof(ncomponents::VertexHolder), (void *)0);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                        sizeof(ncomponents::VertexHolder),
                        (void *)offsetof(ncomponents::VertexHolder, normal_m));

#ifndef PLATFORM_RASPBERRY_PI
  glBindVertexArray(0);
#endif
}

void OpenGLVertexIndexBuffer::deleteBuffers()
{
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glDeleteBuffers(1, &glIBO_m);
  glDeleteBuffers(1, &glVBO_m);
#ifndef PLATFORM_RASPBERRY_PI
  glDeleteVertexArrays(1, &glVAO_m);
#endif
}

void OpenGLVertexIndexBuffer::bind()
{
#ifdef PLATFORM_RASPBERRY_PI
  // For OpenGL ES, manually bind buffers and set up vertex attributes
  glBindBuffer(GL_ARRAY_BUFFER, glVBO_m);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glIBO_m);
  
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                        sizeof(ncomponents::VertexHolder),
                        (void *)offsetof(ncomponents::VertexHolder, pos_m));

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                        sizeof(ncomponents::VertexHolder),
                        (void *)offsetof(ncomponents::VertexHolder, normal_m));
#else
  glBindVertexArray(glVAO_m);
#endif
}

void OpenGLVertexIndexBuffer::unbind()
{
#ifdef PLATFORM_RASPBERRY_PI
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
#else
  glBindVertexArray(0);
#endif
}

void OpenGLVertexIndexBuffer::draw(int indexCount)
{
  bind();

  /* the vertices as line loop */
  glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);

  unbind();
}

} // namespace nrender
