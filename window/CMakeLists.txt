# List all source files in this directory
set(WINDOW_SOURCES
    orbWindow.cpp
)

# Create a library or add to the executable
add_library(window_lib STATIC ${WINDOW_SOURCES})
target_include_directories(window_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Optionally link the library to the executable
# target_link_libraries(mscope PRIVATE window_lib)
