#!/bin/bash

# μscope Installer for Raspberry Pi 5
# Self-extracting installer with embedded payload

set -e

echo "🚀 μscope Installer for Raspberry Pi 5"
echo "======================================"
echo ""

# Check if running on Raspberry Pi
if ! grep -q "Raspberry Pi" /proc/device-tree/model 2>/dev/null; then
    echo "⚠️  Warning: This installer is designed for Raspberry Pi systems."
    read -p "Continue anyway? (y/N): " -n 1 -r
    echo
    if [[ ! $REPLY =~ ^[Yy]$ ]]; then
        echo "Installation cancelled."
        exit 1
    fi
fi

# Check for required commands
for cmd in tar sudo; do
    if ! command -v $cmd >/dev/null 2>&1; then
        echo "❌ Error: $cmd is required but not installed."
        exit 1
    fi
done

echo "📦 Installing dependencies..."
sudo apt update >/dev/null 2>&1
sudo apt install -y libglfw3-dev libopengl0 libgl1-mesa-dev libegl1-mesa-dev libgles2-mesa-dev libglm-dev libstb-dev >/dev/null 2>&1

echo "📁 Extracting and installing mscope..."

# Find the line number where the payload starts
PAYLOAD_LINE=$(awk '/^__PAYLOAD_BELOW__/ {print NR + 1; exit 0; }' "$0")

# Create temporary directory
TEMP_DIR=$(mktemp -d)
trap "rm -rf $TEMP_DIR" EXIT

# Extract payload
tail -n +$PAYLOAD_LINE "$0" | base64 -d | tar -xzf - -C "$TEMP_DIR"

# Install files
sudo mkdir -p /usr/local/bin/mscope
sudo cp "$TEMP_DIR"/mscope /usr/local/bin/mscope/
sudo cp -r "$TEMP_DIR"/fonts /usr/local/bin/mscope/
sudo cp -r "$TEMP_DIR"/shader /usr/local/bin/mscope/
sudo chmod +x /usr/local/bin/mscope/mscope

# Install launcher
sudo cp "$TEMP_DIR"/mscope-launcher /usr/local/bin/
sudo chmod +x /usr/local/bin/mscope-launcher

# Install desktop entry
if [ -f "$TEMP_DIR/mscope.desktop" ]; then
    sudo cp "$TEMP_DIR"/mscope.desktop /usr/share/applications/
    if [ -f "$TEMP_DIR/mscope.png" ]; then
        sudo cp "$TEMP_DIR"/mscope.png /usr/share/pixmaps/
    fi
fi

echo ""
echo "✅ μscope installed successfully!"
echo ""
echo "🎯 You can now run mscope by:"
echo "   • Command line: mscope-launcher"
echo "   • Desktop: Find 'mscope' in your Applications menu"
echo ""
echo "📊 Features:"
echo "   • Real-time data visualization"
echo "   • Serial communication support (/dev/ttyACM0)"
echo "   • CSV data recording"
echo "   • Up to 3 data channels (Lite version)"
echo ""
echo "📝 Note: Add your user to dialout group for serial access:"
echo "   sudo usermod -a -G dialout \$USER"
echo "   (Then logout and login again)"
echo ""
echo "🚀 Installation complete! Enjoy using μscope!"

exit 0

__PAYLOAD_BELOW__ 