# mscope for Raspberry Pi

Real-time serial data visualizer software for microcontrollers.

## Quick Install

1. **Install dependencies:**
   ```bash
   sudo apt update
   sudo apt install libglfw3-dev libopengl0 libgl1-mesa-dev libegl1-mesa-dev libgles2-mesa-dev libglm-dev libstb-dev
   ```

2. **Run the installer:**
   ```bash
   chmod +x install.sh
   ./install.sh
   ```

3. **Launch mscope:**
   - From Applications menu: Look for "mscope"
   - From terminal: `mscope-launcher`
   - Direct: `cd /usr/local/bin/mscope && ./mscope`

## Features

- Real-time serial data visualization
- Multiple graph types
- CSV data recording
- Modern GUI interface
- Optimized for Raspberry Pi

## Requirements

- Raspberry Pi (ARM64)
- Raspberry Pi OS or compatible Linux
- OpenGL ES 2.0 support
