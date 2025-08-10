# @file      CMakeLists.txt
# @brief     Main build configuration file for mscope RPi project
# @author    arturodlrios
# @date      Created on 2024/08/29
#
# This software is the exclusive property of Cortx and is provided
# under strict confidentiality. It is intended for use solely by authorized
# personnel of Cortx and is protected by intellectual property laws.
# Unauthorized use, reproduction, or distribution in whole or in part is scrictly prohibited.
#
# COPYRIGHT NOTICE: 2025 Cortx, Montreal, QC. All rights reserved.
#

#-------------------------------------------------------------------------------
# Project configuration
#-------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.10)
project(mscope VERSION 1.0 LANGUAGES CXX)

#-------------------------------------------------------------------------------
# Set C++ compiler options
#-------------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#-------------------------------------------------------------------------------
# Raspberry Pi specific configuration
#-------------------------------------------------------------------------------

# Add definitions for Raspberry Pi
add_definitions(-DPLATFORM_RASPBERRY_PI)
add_definitions(-DIMGUI_IMPL_OPENGL_ES2)

# Add subdirectories
add_subdirectory(app)
add_subdirectory(components)
add_subdirectory(render)
add_subdirectory(serial)
add_subdirectory(shader)
add_subdirectory(ui)
add_subdirectory(window)
add_subdirectory(backends)

# List all source files
file(GLOB_RECURSE SOURCES
    "app/*.cpp"
    "components/*.cpp"
    "render/*.cpp"
    "serial/*.cpp"
    "shader/*.cpp"
    "ui/*.cpp"
    "window/*.cpp"
    "backends/*.cpp"
    "source/main.cpp"
)

#-------------------------------------------------------------------------------
# Raspberry Pi target configuration
#-------------------------------------------------------------------------------

# Use system libraries via pkg-config
find_package(PkgConfig REQUIRED)

# Try to find GLFW3 using pkg-config, fallback to find_package if not found
pkg_check_modules(PC_GLFW3 QUIET glfw3)
if(PC_GLFW3_FOUND)
    set(GLFW3_DEFINITIONS ${PC_GLFW3_CFLAGS_OTHER})
    set(GLFW3_INCLUDE_DIRS ${PC_GLFW3_INCLUDE_DIRS})
    set(GLFW3_LIBRARIES ${PC_GLFW3_LIBRARIES})
else()
    find_package(glfw3 REQUIRED)
    set(GLFW3_LIBRARIES glfw)
endif()

# Register executable target
add_executable(mscope ${SOURCES})

# Pthread dependency
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# Add libraries/dependencies to executable - RPi uses OpenGL ES
target_link_libraries(mscope PRIVATE
    ${GLFW3_LIBRARIES}
    ${CMAKE_DL_LIBS}
    Threads::Threads
    dl
    pthread
    # For Raspberry Pi, use OpenGL ES instead of desktop OpenGL
    GLESv2
    EGL
)

# Add include directories and compiler flags
target_include_directories(mscope PRIVATE
    ${GLFW3_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/dependencies/include
    ${CMAKE_SOURCE_DIR}/app
    ${CMAKE_SOURCE_DIR}/components
    ${CMAKE_SOURCE_DIR}/render
    ${CMAKE_SOURCE_DIR}/serial
    ${CMAKE_SOURCE_DIR}/shader
    ${CMAKE_SOURCE_DIR}/ui
    ${CMAKE_SOURCE_DIR}/window
    ${CMAKE_SOURCE_DIR}/backends
    ${CMAKE_SOURCE_DIR}/pch
    ${CMAKE_SOURCE_DIR}/Libraries
)

target_compile_options(mscope PRIVATE
    ${GLFW3_DEFINITIONS}
)

# Copy fonts to binary build directory
add_custom_command(TARGET mscope POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/fonts $<TARGET_FILE_DIR:mscope>/fonts
)

# Copy shader files to binary build directory
file(GLOB SHADER_FILES "${CMAKE_SOURCE_DIR}/shader/*.shader")
foreach(SHADER_FILE ${SHADER_FILES})
    add_custom_command(TARGET mscope POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${SHADER_FILE} $<TARGET_FILE_DIR:mscope>/shader
    )
endforeach()

# Copy RPi specific shaders
add_custom_command(TARGET mscope POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/shader/trivs_rpi.shader $<TARGET_FILE_DIR:mscope>/shader/
)
add_custom_command(TARGET mscope POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/shader/trifs_rpi.shader $<TARGET_FILE_DIR:mscope>/shader/
)

#-------------------------------------------------------------------------------
# Installation - RPi specific
#-------------------------------------------------------------------------------

# Install the application binary to /usr/local/bin
install(TARGETS mscope RUNTIME DESTINATION /usr/local/bin)

# Install the font files
install(DIRECTORY ${CMAKE_SOURCE_DIR}/fonts DESTINATION /usr/local/bin/mscope)

# Install shader files
file(GLOB SHADER_FILES "${CMAKE_SOURCE_DIR}/shader/*.shader")
install(FILES ${SHADER_FILES} DESTINATION /usr/local/bin/mscope/shader)

#-------------------------------------------------------------------------------
# Packaging - RPi specific
#-------------------------------------------------------------------------------

set(CPACK_PACKAGE_NAME                  mscope-rpi)
set(CPACK_PACKAGE_CONTACT               contact@cortx.com)
set(CPACK_PACKAGE_VENDOR                Cortx)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY   Real-time serial data visualizer for Raspberry Pi)
set(CPACK_PACKAGE_VERSION_MAJOR         1)
set(CPACK_PACKAGE_VERSION_MINOR         0)
set(CPACK_PACKAGE_VERSION_PATCH         0)
set(CPACK_PACKAGE_FILE_NAME             mscope-rpi-1.0.0)
set(CPACK_GENERATOR                     "TGZ")

include(CPack)
 