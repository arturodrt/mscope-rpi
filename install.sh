#!/bin/bash

echo "🚀 Installing μscope for Raspberry Pi 5..."
echo "========================================"

# Check if running on Raspberry Pi
if [[ ! -f /proc/device-tree/model ]] || ! grep -q "Raspberry Pi" /proc/device-tree/model 2>/dev/null; then
    echo "⚠️  Warning: This installer is designed for Raspberry Pi systems."
    read -p "Continue anyway? (y/N): " -n 1 -r
    echo
    if [[ ! $REPLY =~ ^[Yy]$ ]]; then
        echo "Installation cancelled."
        exit 1
    fi
fi

echo "📦 Installing dependencies..."

# Update package list
sudo apt update

# Install required packages
sudo apt install -y \
    libglfw3-dev \
    libopengl0 \
    libgl1-mesa-dev \
    libegl1-mesa-dev \
    libgles2-mesa-dev \
    libglm-dev \
    libstb-dev

echo "📁 Installing mscope..."

# Create installation directory
sudo mkdir -p /usr/local/bin/mscope

# Copy binary and support files
sudo cp mscope /usr/local/bin/mscope/
sudo cp -r fonts /usr/local/bin/mscope/
sudo cp -r shader /usr/local/bin/mscope/

# Set executable permissions
sudo chmod +x /usr/local/bin/mscope/mscope

# Install launcher script
sudo cp mscope-launcher /usr/local/bin/
sudo chmod +x /usr/local/bin/mscope-launcher

# Install icon to pixmaps directory (standard location)
sudo cp mscope.png /usr/local/bin/mscope/
sudo cp mscope.png /usr/share/pixmaps/

# Create proper desktop entry
sudo tee /usr/share/applications/mscope.desktop > /dev/null << 'EOF'
[Desktop Entry]
Name=mscope
Comment=Real-time serial data visualizer software for microcontrollers
Exec=mscope-launcher
Terminal=false
Type=Application
StartupNotify=true
Categories=Electronics;Engineering;Science;Programming;
Icon=mscope
EOF

# Refresh desktop database and icon cache
sudo update-desktop-database /usr/share/applications 2>/dev/null || true
sudo gtk-update-icon-cache /usr/share/pixmaps 2>/dev/null || true

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