# List all source files in this directory
set(SHADER_SOURCES
    shaderUtil.cpp
)

# Create a library or add to the executable
add_library(shader_lib STATIC ${SHADER_SOURCES})
target_include_directories(shader_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Optionally link the library to the executable
# target_link_libraries(mscope PRIVATE shader_lib)
