# List all source files in this directory
set(BACKENDS_SOURCES
    imgui.cpp
    imguiCustomThemes.cpp
    imgui_demo.cpp
    imgui_draw.cpp
    imgui_impl_glfw.cpp
    imgui_impl_opengl3.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
    implot.cpp
    implot_items.cpp
)

# Create a library or add to the executable
add_library(backends_lib STATIC ${BACKENDS_SOURCES})

target_include_directories(backends_lib PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/dependencies/include
)


# Optionally link the library to the executable
# target_link_libraries(mscope PRIVATE backends_lib)
