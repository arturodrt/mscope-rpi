#!/bin/bash

set -e

echo "🚀 Installing mscope for Raspberry Pi..."

# Check if running on Raspberry Pi
if ! grep -q "Raspberry Pi" /proc/cpuinfo 2>/dev/null; then
    echo "❌ This installer is for Raspberry Pi only"
    exit 1
fi

# Install dependencies
echo "📦 Installing dependencies..."
sudo apt update
sudo apt install -y libglfw3-dev libopengl0 libgl1-mesa-dev libegl1-mesa-dev libgles2-mesa-dev libglm-dev libstb-dev

# Create installation directory
sudo mkdir -p /usr/local/bin/mscope

# Copy files
echo "📁 Installing mscope..."
sudo cp mscope /usr/local/bin/mscope/
sudo cp -r fonts /usr/local/bin/mscope/
sudo cp -r shader /usr/local/bin/mscope/
sudo chmod +x /usr/local/bin/mscope/mscope

# Create launcher script
sudo cp mscope-launcher /usr/local/bin/
sudo chmod +x /usr/local/bin/mscope-launcher

# Install desktop shortcut
sudo cp mscope.desktop /usr/share/applications/

echo "✅ mscope installed successfully!"
echo "🎯 You can now run 'mscope-launcher' or find 'mscope' in your Applications menu"
