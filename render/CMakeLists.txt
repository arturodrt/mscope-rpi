# List all source files in this directory
set(RENDER_SOURCES
    openglBufferManagement.cpp
    openglContext.cpp
    uiContext.cpp
)

# Create a library or add to the executable
add_library(render_lib STATIC ${RENDER_SOURCES})
target_include_directories(render_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Optionally link the library to the executable
