# List all source files in this directory
set(UI_SOURCES
    csvRecordingSettings.cpp
    dataReceptionSettings.cpp
    generalSettings.cpp
    sceneView.cpp
    serialSettings.cpp
    serialTerminal.cpp
    settings.cpp
    viewerSettings.cpp
    visualizer.cpp
)

# Create a library or add to the executable
add_library(ui_lib STATIC ${UI_SOURCES})
target_include_directories(ui_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Optionally link the library to the executable
# target_link_libraries(mscope PRIVATE ui_lib)
