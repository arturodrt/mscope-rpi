#!/bin/bash

# Raspberry Pi Cross-Compilation Build Script
# This script builds mscope for Raspberry Pi

set -e

echo "Building mscope for Raspberry Pi..."

# Check if we're on a supported host system
if [[ "$(uname -m)" != "x86_64" ]]; then
    echo "Error: This script is designed to run on x86_64 hosts for cross-compilation"
    exit 1
fi

# Check if cross-compiler is installed
if ! command -v aarch64-linux-gnu-gcc &> /dev/null; then
    echo "Error: ARM64 cross-compiler not found"
    echo "Please install the cross-compilation toolchain:"
    echo "  sudo apt install gcc-aarch64-linux-gnu g++-aarch64-linux-gnu"
    exit 1
fi

# Check if rpi_files sysroot is available
if [ ! -d "deploy/rpi_files" ]; then
    echo "Error: rpi_files sysroot not found at deploy/rpi_files"
    echo "Please ensure the rpi_files directory exists in the deploy folder"
    exit 1
fi

# Create build directory
mkdir -p build-raspberry-pi
cd build-raspberry-pi

# Configure with cross-compilation toolchain
echo "Configuring CMake for Raspberry Pi..."
cmake -DCMAKE_TOOLCHAIN_FILE=../raspberry-pi-toolchain.cmake ..

# Build
echo "Building mscope..."
make -j$(nproc)

echo "Build completed successfully!"
echo "The Raspberry Pi executable is in: build-raspberry-pi/mscope"
echo ""
echo "To deploy to Raspberry Pi:"
echo "1. Copy the executable: scp mscope pi@raspberrypi.local:/home/pi/"
echo "2. Copy fonts: scp -r fonts/ pi@raspberrypi.local:/home/pi/"
echo "3. Copy shaders: scp -r shader/ pi@raspberrypi.local:/home/pi/" 