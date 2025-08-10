# CMake toolchain file for Raspberry Pi cross-compilation
# This file configures CMake to cross-compile for Raspberry Pi (ARM64/aarch64)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

# Cross compiler tools
set(CMAKE_C_COMPILER aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++)

# Determine sysroot path based on environment
# Check if we're in GitHub Actions or local development
if(DEFINED ENV{GITHUB_WORKSPACE})
    # GitHub Actions environment
    set(SYSROOT_PATH "$ENV{GITHUB_WORKSPACE}/deploy/rpi_files")
    message(STATUS "Using GitHub Actions sysroot: ${SYSROOT_PATH}")
elseif(DEFINED CMAKE_SYSROOT AND EXISTS ${CMAKE_SYSROOT})
    # CMake command line provided sysroot (highest priority for local builds)
    set(SYSROOT_PATH ${CMAKE_SYSROOT})
    message(STATUS "Using provided sysroot: ${SYSROOT_PATH}")
else()
    # Local development - try common paths
    set(POTENTIAL_PATHS
        "${CMAKE_SOURCE_DIR}/deploy/rpi_files"
        "${CMAKE_SOURCE_DIR}/../deploy/rpi_files" 
        "${CMAKE_CURRENT_SOURCE_DIR}/deploy/rpi_files"
        "/opt/rpi-sysroot"
        "$ENV{HOME}/rpi_files"
        "C:/Users/$ENV{USERNAME}/Documents/rpi_files"
    )
    
    foreach(PATH ${POTENTIAL_PATHS})
        if(EXISTS ${PATH}/usr/include AND EXISTS ${PATH}/usr/lib)
            set(SYSROOT_PATH ${PATH})
            message(STATUS "Found local sysroot: ${SYSROOT_PATH}")
            break()
        endif()
    endforeach()
    
    if(NOT DEFINED SYSROOT_PATH)
        message(FATAL_ERROR 
            "Could not find Raspberry Pi sysroot. Please:\n"
            "1. Extract rpi_files.zip in your project directory, OR\n"
            "2. Set CMAKE_SYSROOT when running cmake:\n"
            "   cmake .. -DCMAKE_TOOLCHAIN_FILE=raspberry-pi-toolchain.cmake -DCMAKE_SYSROOT=/path/to/rpi_files\n"
            "Searched paths: ${POTENTIAL_PATHS}")
    endif()
endif()

# Convert to absolute path and normalize
get_filename_component(SYSROOT_PATH ${SYSROOT_PATH} ABSOLUTE)
message(STATUS "Using sysroot: ${SYSROOT_PATH}")

# Verify sysroot structure
if(NOT EXISTS ${SYSROOT_PATH}/usr/include)
    message(FATAL_ERROR "Invalid sysroot: ${SYSROOT_PATH}/usr/include not found")
endif()

if(NOT EXISTS ${SYSROOT_PATH}/usr/lib)
    message(FATAL_ERROR "Invalid sysroot: ${SYSROOT_PATH}/usr/lib not found")
endif()

# Set the sysroot
set(CMAKE_SYSROOT ${SYSROOT_PATH})
set(CMAKE_FIND_ROOT_PATH ${SYSROOT_PATH})

# Configure search behavior
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)   # Don't search for programs in sysroot
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY BOTH)    # Search for libraries in sysroot first, then system
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE BOTH)    # Search for headers in sysroot first, then system
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE BOTH)    # Search for packages in sysroot first, then system

# Compiler flags for ARM64
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -march=armv8-a")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=armv8-a")

# Use the sysroot's glibc version to avoid compatibility issues
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --sysroot=${SYSROOT_PATH}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --sysroot=${SYSROOT_PATH}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --sysroot=${SYSROOT_PATH}")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} --sysroot=${SYSROOT_PATH}")

# Set up pkg-config for cross-compilation
# Use native pkg-config since ARM64 version may not be available
set(PKG_CONFIG_EXECUTABLE pkg-config)

# Configure pkg-config paths
set(ENV{PKG_CONFIG_PATH} "")
set(ENV{PKG_CONFIG_LIBDIR} "${SYSROOT_PATH}/usr/lib/aarch64-linux-gnu/pkgconfig:${SYSROOT_PATH}/usr/share/pkgconfig:${SYSROOT_PATH}/usr/lib/pkgconfig")
set(ENV{PKG_CONFIG_SYSROOT_DIR} "${SYSROOT_PATH}")

# Set the target architecture for library path
set(CMAKE_LIBRARY_ARCHITECTURE aarch64-linux-gnu)

# Additional library paths for the linker
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L${SYSROOT_PATH}/usr/lib/aarch64-linux-gnu -L/usr/aarch64-linux-gnu/lib")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -L${SYSROOT_PATH}/usr/lib/aarch64-linux-gnu -L/usr/aarch64-linux-gnu/lib")

# Help CMake find libraries in the sysroot
list(APPEND CMAKE_PREFIX_PATH "${SYSROOT_PATH}/usr")
list(APPEND CMAKE_PREFIX_PATH "${SYSROOT_PATH}/usr/local")

# Add the library architecture path explicitly
set(CMAKE_LIBRARY_PATH "${SYSROOT_PATH}/usr/lib/aarch64-linux-gnu;${SYSROOT_PATH}/usr/lib")
set(CMAKE_INCLUDE_PATH "${SYSROOT_PATH}/usr/include")

# Debug information
message(STATUS "Cross-compiling for Raspberry Pi ARM64")
message(STATUS "C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "CXX Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "Sysroot: ${CMAKE_SYSROOT}")
message(STATUS "PKG_CONFIG_LIBDIR: $ENV{PKG_CONFIG_LIBDIR}")

# Verify toolchain works by testing compiler
execute_process(
    COMMAND ${CMAKE_C_COMPILER} --version
    RESULT_VARIABLE COMPILER_TEST_RESULT
    OUTPUT_QUIET ERROR_QUIET
)

if(NOT COMPILER_TEST_RESULT EQUAL 0)
    message(FATAL_ERROR 
        "Cross-compiler not found: ${CMAKE_C_COMPILER}\n"
        "Please install the ARM64 cross-compilation toolchain:\n"
        "Ubuntu/Debian: sudo apt-get install gcc-aarch64-linux-gnu g++-aarch64-linux-gnu\n"
        "Or install via your distribution's package manager")
endif()

message(STATUS "Toolchain configuration complete")
