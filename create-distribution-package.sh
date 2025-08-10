#!/bin/bash

set -e

echo "📦 Creating mscope Distribution Package for Raspberry Pi"
echo "======================================================"

# Check if we're on Raspberry Pi
if grep -q "Raspberry Pi" /proc/cpuinfo 2>/dev/null; then
    echo "🍓 Building natively on Raspberry Pi..."
    
    # Install dependencies
    echo "📦 Installing dependencies..."
    sudo apt update
    sudo apt install -y cmake build-essential libglfw3-dev libopengl0 libgl1-mesa-dev libegl1-mesa-dev libgles2-mesa-dev libglm-dev libstb-dev
    
    # Build the ARM64 binary natively
    echo "🔨 Building ARM64 binary..."
    mkdir -p build-raspberry-pi
    cd build-raspberry-pi
    
    cmake .. -DPLATFORM_RASPBERRY_PI=ON
    make -j$(nproc)
    
else
    echo "❌ This script should be run on a Raspberry Pi for native building"
    echo "   Cross-compilation is complex and requires additional setup"
    echo "   Please run this script on your Raspberry Pi"
    exit 1
fi

# Create distribution package
echo "📁 Creating distribution package..."
mkdir -p mscope-arm64-package
cp mscope mscope-arm64-package/
cp -r ../fonts mscope-arm64-package/
cp -r ../shader mscope-arm64-package/

# Create launcher script
cat > mscope-arm64-package/mscope-launcher << 'EOF'
#!/bin/bash
cd "$(dirname "$0")"
export DISPLAY=:0
./mscope "$@"
EOF
chmod +x mscope-arm64-package/mscope-launcher

# Create desktop file
cat > mscope-arm64-package/mscope.desktop << 'EOF'
[Desktop Entry]
Name=mscope
Comment=Real-time serial data visualizer software for microcontrollers
Exec=mscope-launcher
Terminal=false
Type=Application
StartupNotify=true
Categories=Electronics;Engineering;Science;
Icon=mscope.png
EOF

# Create install script
cat > mscope-arm64-package/install.sh << 'EOF'
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
EOF
chmod +x mscope-arm64-package/install.sh

# Create README
cat > mscope-arm64-package/README.md << 'EOF'
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
EOF

# Create tarball
VERSION=$(date +%Y%m%d)
tar czf "../mscope-arm64-v$VERSION.tar.gz" mscope-arm64-package/

cd ..

echo ""
echo "✅ Distribution package created: mscope-arm64-v$VERSION.tar.gz"
echo ""
echo "📋 To distribute to users:"
echo "1. Upload mscope-arm64-v$VERSION.tar.gz to your preferred file sharing service"
echo "2. Users download and extract: tar xzf mscope-arm64-v$VERSION.tar.gz"
echo "3. Users run: cd mscope-arm64-package && ./install.sh"
echo ""
echo "🎯 Users can install with just:"
echo "   tar xzf mscope-arm64-v$VERSION.tar.gz && cd mscope-arm64-package && ./install.sh" 