#pragma once
/** @file      pch.h
 *  @brief     Precompiled header.
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

/* Std includes */
#include <string>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>

/* GL includes - Raspberry Pi uses OpenGL ES directly */
  #include <GLES2/gl2.h>
  #include <GLES2/gl2ext.h>
#include "../dependencies/include/GLFW/glfw3.h"
#include "../dependencies/include/GLFW/glfw3native.h"

#include "../dependencies/include/glm/glm.hpp"
#include "../dependencies/include/glm/gtc/matrix_transform.hpp"
#include "../dependencies/include/glm/gtc/type_ptr.hpp"
#include "../dependencies/include/glm/gtx/transform.hpp"

#include "../Libraries/lib.h"
