# Define the main executable
add_executable(mscope main.cpp)

# Optionally link libraries
target_link_libraries(mscope
    PRIVATE
    app_lib
    components_lib
    render_lib
    serial_lib
    shader_lib
    ui_lib
    window_lib
    backends_lib
)
