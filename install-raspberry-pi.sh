#!/bin/bash

set -e

echo "🚀 mscope Raspberry Pi Installer"
echo "================================"

# Check if running on Raspberry Pi
if ! grep -q "Raspberry Pi" /proc/cpuinfo 2>/dev/null; then
    echo "❌ This installer is for Raspberry Pi only"
    echo "   Please run this script on a Raspberry Pi device"
    exit 1
fi

# Check if running as root
if [ "$EUID" -eq 0 ]; then
    echo "❌ Please don't run this script as root"
    echo "   Run: sudo ./install-raspberry-pi.sh"
    exit 1
fi

# Get the latest release
LATEST_RELEASE=$(curl -s https://api.github.com/repos/arturodlrios/mscope/releases/latest | grep '"tag_name"' | cut -d'"' -f4)

if [ -z "$LATEST_RELEASE" ]; then
    echo "❌ Could not find latest release"
    echo "   Please check: https://github.com/arturodlrios/mscope/releases"
    exit 1
fi

echo "📦 Installing mscope version: $LATEST_RELEASE"

# Create temporary directory
TEMP_DIR=$(mktemp -d)
cd "$TEMP_DIR"

# Download the latest ARM64 binary
echo "⬇️  Downloading mscope ARM64 binary..."
wget -q "https://github.com/arturodlrios/mscope/releases/download/$LATEST_RELEASE/mscope-arm64-$(date +%Y%m%d).tar.gz" || {
    echo "❌ Failed to download binary"
    echo "   Please check your internet connection and try again"
    exit 1
}

# Extract the package
echo "📁 Extracting package..."
tar xzf mscope-arm64-*.tar.gz
cd mscope-arm64-package

# Install dependencies
echo "📦 Installing dependencies..."
sudo apt update
sudo apt install -y libglfw3-dev libopengl0 libgl1-mesa-dev libegl1-mesa-dev libgles2-mesa-dev libglm-dev libstb-dev

# Run the installer
echo "🔧 Installing mscope..."
chmod +x install.sh
./install.sh

# Clean up
cd /
rm -rf "$TEMP_DIR"

echo ""
echo "🎉 mscope installed successfully!"
echo "================================"
echo "You can now:"
echo "  • Launch from Applications menu: Look for 'mscope'"
echo "  • Run from terminal: mscope-launcher"
echo "  • Run directly: cd /usr/local/bin/mscope && ./mscope"
echo ""
echo "For help and documentation, visit:"
echo "  https://github.com/arturodlrios/mscope"
echo "" 