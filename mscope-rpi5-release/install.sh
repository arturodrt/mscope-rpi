#!/bin/bash

echo "🚀 Installing μscope for Raspberry Pi 5..."
echo "========================================"

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

# Install dependencies
echo "📦 Installing dependencies..."
sudo apt update
sudo apt install -y libglfw3-dev libopengl0 libgl1-mesa-dev libegl1-mesa-dev libgles2-mesa-dev libglm-dev libstb-dev

# Create installation directory
echo "📁 Installing mscope..."
sudo mkdir -p /usr/local/bin/mscope
sudo cp mscope /usr/local/bin/mscope/
sudo cp -r fonts /usr/local/bin/mscope/
sudo cp -r shader /usr/local/bin/mscope/
sudo chmod +x /usr/local/bin/mscope/mscope

# Install launcher
sudo cp mscope-launcher /usr/local/bin/
sudo chmod +x /usr/local/bin/mscope-launcher

# Install desktop entry
if [ -f mscope.desktop ]; then
    sudo cp mscope.desktop /usr/share/applications/
sudo cp mscope.png /usr/share/pixmaps/
    if [ -f mscope.png ]; then
        sudo cp mscope.png /usr/share/pixmaps/
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
echo "📝 Note: Make sure your user is in the 'dialout' group for serial access:"
echo "   sudo usermod -a -G dialout \$USER"
echo "   (Then logout and login again)"
