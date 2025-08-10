# List all source files in this directory
set(COMPONENTS_SOURCES
    graph.cpp
    triangle.cpp
)

# Create a library or add to the executable
add_library(components_lib STATIC ${COMPONENTS_SOURCES})
target_include_directories(components_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Optionally link the library to the executable
# target_link_libraries(mscope PRIVATE components_lib)
