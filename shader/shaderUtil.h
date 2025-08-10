#pragma once
/** @file      shaderUtil.h
 *  @brief     Header file for the shader functions.
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

namespace nshaders
{
/* Utitlity class to load, compile and attach a vertex and fragment shader to a
 * program */
class Shader
{
public:
  Shader(void) = default;

  /* Load a vertex and a fragment shader from file */
  OrbCode_t load(const std::string &vertexShaderFile,
                 const std::string &fragmentShaderFile);

  /* Use the program */
  void use(void);

  /* Delete the program */
  void unload(void);

  uint32_t ulGetProgramId() { return glProgramId_m; }

  void num(std::string const &name, uint32_t const &count, float const *value);

  void set_mat4(const glm::mat4 &mat4, const std::string &name);

  void set_vec3(const glm::vec3 &vec3, const std::string &name);

private:
  uint32_t getCompiledShader(uint32_t shaderType,
                             const std::string &shaderSource);

  uint32_t glProgramId_m;
};
} // namespace nshaders
/* -------------------------------------------------------------------------------------------
 */
