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

# Install icon
echo "🖼️  Installing icon..."
sudo cp mscope.png /usr/share/pixmaps/mscope.png
sudo chmod 644 /usr/share/pixmaps/mscope.png

# Create launcher script
echo "🔗 Creating launcher script..."
sudo tee /usr/local/bin/mscope-launcher > /dev/null << 'EOF'
#!/bin/bash
cd /usr/local/bin/mscope
./mscope
EOF
sudo chmod +x /usr/local/bin/mscope-launcher

# Create desktop shortcut
echo "🖥️  Creating desktop shortcut..."
sudo tee /usr/share/applications/mscope.desktop > /dev/null << 'EOF'
[Desktop Entry]
Version=1.0
Type=Application
Name=mscope
Comment=Real-time serial data visualizer for Raspberry Pi
Exec=/usr/local/bin/mscope-launcher
Icon=/usr/share/pixmaps/mscope.png
Terminal=false
Type=Application
Categories=Development;Engineering;Electronics;
StartupNotify=true
Keywords=serial;data;visualization;oscilloscope;
EOF

# Update desktop database
if command -v update-desktop-database >/dev/null 2>&1; then
    echo "🔄 Updating desktop database..."
    sudo update-desktop-database /usr/share/applications/ 2>/dev/null || true
fi

echo "✅ mscope installed successfully!"
echo "🎯 You can now run 'mscope-launcher' or find 'mscope' in your Applications menu"
echo "🖼️  Icon installed at /usr/share/pixmaps/mscope.png"
echo ""
echo "📖 For more information, visit: https://cortxtech.com" 