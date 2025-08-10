/** @file      shaderUtil.c
 *  @brief     Source file for the shader functions.
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
#include "shaderUtil.h"
/* Namespaces
 * --------------------------------------------------------------------------------
 */

namespace nshaders
{
OrbCode_t Shader::load(const std::string &vertexShaderFile,
                       const std::string &fragmentShaderFile)
{
  std::ifstream isVs(vertexShaderFile);
  const std::string fVs((std::istreambuf_iterator<char>(isVs)),
                        std::istreambuf_iterator<char>());

  std::ifstream isFs(fragmentShaderFile);
  const std::string fFs((std::istreambuf_iterator<char>(isFs)),
                        std::istreambuf_iterator<char>());

  glProgramId_m = glCreateProgram();

  uint32_t ulVs = getCompiledShader(GL_VERTEX_SHADER, fVs);
  uint32_t ulFs = getCompiledShader(GL_FRAGMENT_SHADER, fFs);

  glAttachShader(glProgramId_m, ulVs);
  glAttachShader(glProgramId_m, ulFs);

  glLinkProgram(glProgramId_m);
  glValidateProgram(glProgramId_m);

  glDeleteShader(ulVs);
  glDeleteShader(ulFs);

  return Success;
}

uint32_t Shader::getCompiledShader(uint32_t shaderType,
                                   const std::string &shaderSource)
{

  uint32_t ulShaderId = glCreateShader(shaderType);

  const char *cSource = shaderSource.c_str();
  glShaderSource(ulShaderId, 1, &cSource, nullptr);
  glCompileShader(ulShaderId);

  GLint glResult;
  glGetShaderiv(ulShaderId, GL_COMPILE_STATUS, &glResult);

  if (glResult == GL_FALSE)
  {
    int32_t slLength;
    glGetShaderiv(ulShaderId, GL_INFO_LOG_LENGTH, &slLength);

    GLchar *cInfoLog = new GLchar[slLength + 1];
    glGetShaderInfoLog(ulShaderId, slLength, &slLength, cInfoLog);

    fprintf(stderr, "Compile error in shader: %s\n", cInfoLog);
    delete[] cInfoLog;
  }

  return ulShaderId;
}

void Shader::use()
{
  glUseProgram(glProgramId_m);
}

void Shader::unload()
{
  glDeleteProgram(glProgramId_m);
}

void Shader::num(std::string const &name, uint32_t const &count,
                 float const *value)
{
  GLint myLoc = glGetUniformLocation(ulGetProgramId(), name.c_str());
  glUniform1fv(myLoc, count, value);
}

void Shader::set_mat4(const glm::mat4 &mat4, const std::string &name)
{
  GLint myLoc = glGetUniformLocation(ulGetProgramId(), name.c_str());
  glUniformMatrix4fv(myLoc, 1, GL_FALSE, glm::value_ptr(mat4));
}

void Shader::set_vec3(const glm::vec3 &vec3, const std::string &name)
{
  GLint myLoc = glGetUniformLocation(ulGetProgramId(), name.c_str());
#ifdef PLATFORM_RASPBERRY_PI
  // OpenGL ES 2.0 compatibility - use glUniform3fv instead of glProgramUniform3fv
  glUniform3fv(myLoc, 1, glm::value_ptr(vec3));
#else
  glProgramUniform3fv(ulGetProgramId(), myLoc, 1, glm::value_ptr(vec3));
#endif
}
} // namespace nshaders
/* -------------------------------------------------------------------------------------------
 */
