# Set the list of source files
set(APP_SOURCES
    application.cpp
)

# Create a static library from the source files
add_library(app_lib STATIC ${APP_SOURCES})

# Specify include directories for this target
target_include_directories(app_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})