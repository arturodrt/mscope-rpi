# Raspberry Pi Setup Guide for mscope

This guide explains how to build and run mscope on Raspberry Pi.

## Prerequisites

### On Your Development Machine (x86_64 Linux)

1. **Install Raspberry Pi Toolchain:**
```bash
sudo git clone https://github.com/raspberrypi/tools.git /opt/raspberry-pi-toolchain
```

2. **Set up Raspberry Pi Sysroot:**
```bash
# The rpi_files sysroot is included in the deploy/ directory
# No additional setup required - the build system will automatically
# detect and use the sysroot from deploy/rpi_files/
```

3. **Install Required Dependencies:**
```bash
sudo apt update
sudo apt install -y cmake build-essential pkg-config
```

### On Raspberry Pi

1. **Install Required Packages:**
```bash
sudo apt update
sudo apt install -y \
    libglew-dev \
    libglfw3-dev \
    libopengl0 \
    libgl1-mesa-dev \
    libegl1-mesa-dev \
    libgles2-mesa-dev \
    libraspberrypi-dev \
    libraspberrypi0
```

## Building for Raspberry Pi

### Option 1: Cross-Compilation (Recommended)

1. **Use the build script:**
```bash
./build-raspberry-pi.sh
```

2. **Or manually:**
```bash
mkdir build-raspberry-pi
cd build-raspberry-pi
cmake -DCMAKE_TOOLCHAIN_FILE=../raspberry-pi-toolchain.cmake ..
make -j$(nproc)
```

### Option 2: Native Build on Raspberry Pi

1. **Clone and build directly on Raspberry Pi:**
```bash
git clone <your-repo-url>
cd mscope
mkdir build && cd build
cmake ..
make -j$(nproc)
```

## Deployment

### Cross-Compilation Deployment

1. **Copy the executable:**
```bash
scp build-raspberry-pi/mscope pi@raspberrypi.local:/home/pi/
```

2. **Copy required files:**
```bash
scp -r build-raspberry-pi/fonts/ pi@raspberrypi.local:/home/pi/
scp -r build-raspberry-pi/shader/ pi@raspberrypi.local:/home/pi/
```

### Native Build Deployment

The executable is already on the Raspberry Pi and ready to run.

## Running on Raspberry Pi

1. **SSH into Raspberry Pi:**
```bash
ssh pi@raspberrypi.local
```

2. **Run the application:**
```bash
cd /home/pi
./mscope
```

## Troubleshooting

### Common Issues

1. **"Failed to initialize GLEW"**
   - Make sure you have the latest firmware: `sudo rpi-update`
   - Check if OpenGL is enabled: `vcgencmd get_mem gpu`

2. **"GLFW Window couldn't be created"**
   - Enable X11 forwarding: `ssh -X pi@raspberrypi.local`
   - Or run in headless mode with virtual display

3. **Performance Issues**
   - Overclock your Raspberry Pi (with proper cooling)
   - Use a Raspberry Pi 4 with 4GB+ RAM
   - Close unnecessary background processes

### Performance Optimization

1. **Enable GPU Memory Split:**
```bash
sudo raspi-config
# Navigate to Advanced Options > Memory Split
# Set to 128 or 256 MB
```

2. **Enable Hardware Acceleration:**
```bash
# Add to /boot/config.txt
gpu_mem=256
dtoverlay=vc4-kms-v3d
```

3. **Optimize for Headless Operation:**
```bash
# Disable GUI on boot
sudo raspi-config
# Navigate to Boot Options > Desktop/CLI
# Select "Console Autologin"
```

## Hardware Requirements

- **Minimum:** Raspberry Pi 3B+ with 1GB RAM
- **Recommended:** Raspberry Pi 4 with 4GB+ RAM
- **Storage:** 8GB+ SD card (Class 10 recommended)
- **Cooling:** Active cooling recommended for sustained performance

## Notes

- The application uses OpenGL ES 2.0 on Raspberry Pi
- Performance may be limited compared to desktop systems
- Consider using a headless mode for data acquisition without GUI
- Bluetooth functionality requires additional setup on Raspberry Pi 