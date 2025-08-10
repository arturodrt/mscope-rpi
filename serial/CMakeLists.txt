# List all source files in this directory
set(SERIAL_SOURCES
    serialComms.cpp
    csvStorage.cpp
)

# Create a library or add to the executable
add_library(serial_lib STATIC ${SERIAL_SOURCES})
target_include_directories(serial_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Optionally link the library to the executable
# target_link_libraries(mscope PRIVATE serial_lib)
