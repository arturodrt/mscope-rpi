#!/bin/bash

# Raspberry Pi Deployment Script for mscope
# This script deploys mscope to a Raspberry Pi with proper installation

set -e

# Configuration
RPI_HOST="${1:-pi@raspberrypi.local}"
INSTALL_DIR="/usr/local/bin/mscope"
SERVICE_NAME="mscope"
BUILD_DIR="build-raspberry-pi"

echo "🚀 Deploying mscope to Raspberry Pi..."

# Check if build exists
if [ ! -f "$BUILD_DIR/mscope" ]; then
    echo "❌ Error: Build not found at $BUILD_DIR/mscope"
    echo "Please run ./build-raspberry-pi.sh first"
    exit 1
fi

# Test SSH connection
echo "🔌 Testing SSH connection to $RPI_HOST..."
if ! ssh -o ConnectTimeout=10 -o BatchMode=yes "$RPI_HOST" exit 2>/dev/null; then
    echo "❌ Error: Cannot connect to $RPI_HOST"
    echo "Please ensure:"
    echo "1. Raspberry Pi is accessible via SSH"
    echo "2. SSH key authentication is set up"
    echo "3. Hostname/IP is correct"
    exit 1
fi

echo "✅ SSH connection successful"

# Create installation directory on Raspberry Pi
echo "📁 Creating installation directory..."
ssh "$RPI_HOST" "sudo mkdir -p $INSTALL_DIR"

# Copy executable
echo "📦 Copying executable..."
scp "$BUILD_DIR/mscope" "$RPI_HOST:/tmp/mscope"
ssh "$RPI_HOST" "sudo mv /tmp/mscope $INSTALL_DIR/mscope && sudo chmod +x $INSTALL_DIR/mscope"

# Copy fonts
echo "📝 Copying fonts..."
scp -r "$BUILD_DIR/fonts" "$RPI_HOST:/tmp/"
ssh "$RPI_HOST" "sudo cp -r /tmp/fonts $INSTALL_DIR/"

# Copy shaders
echo "🎨 Copying shaders..."
scp -r "$BUILD_DIR/shader" "$RPI_HOST:/tmp/"
ssh "$RPI_HOST" "sudo cp -r /tmp/shader $INSTALL_DIR/"

# Create desktop shortcut
echo "🖥️ Creating desktop shortcut..."
cat > /tmp/mscope.desktop << EOF
[Desktop Entry]
Name=mscope
Comment=Real-time serial data visualizer software for microcontrollers
Exec=$INSTALL_DIR/mscope
Terminal=false
Type=Application
StartupNotify=true
Categories=Electronics;Engineering;Science;
Icon=mscope
EOF

scp /tmp/mscope.desktop "$RPI_HOST:/tmp/"
ssh "$RPI_HOST" "sudo cp /tmp/mscope.desktop /usr/share/applications/mscope.desktop"

# Copy icon
if [ -f "deploy/linux/mscope.png" ]; then
    echo "🖼️ Copying icon..."
    scp deploy/linux/mscope.png "$RPI_HOST:/tmp/"
    ssh "$RPI_HOST" "sudo cp /tmp/mscope.png /usr/share/pixmaps/mscope.png"
fi

# Create systemd service for headless operation
echo "⚙️ Creating systemd service..."
cat > /tmp/mscope.service << EOF
[Unit]
Description=mscope Serial Data Visualizer
After=network.target

[Service]
Type=simple
User=pi
Group=pi
WorkingDirectory=$INSTALL_DIR
ExecStart=$INSTALL_DIR/mscope
Restart=on-failure
RestartSec=5
Environment=DISPLAY=:0

[Install]
WantedBy=multi-user.target
EOF

scp /tmp/mscope.service "$RPI_HOST:/tmp/"
ssh "$RPI_HOST" "sudo cp /tmp/mscope.service /etc/systemd/system/ && sudo systemctl daemon-reload"

# Create launcher script
echo "🔧 Creating launcher script..."
cat > /tmp/mscope-launcher << EOF
#!/bin/bash
cd $INSTALL_DIR
exec ./mscope "\$@"
EOF

scp /tmp/mscope-launcher "$RPI_HOST:/tmp/"
ssh "$RPI_HOST" "sudo mv /tmp/mscope-launcher /usr/local/bin/mscope-launcher && sudo chmod +x /usr/local/bin/mscope-launcher"

# Clean up temporary files
ssh "$RPI_HOST" "rm -rf /tmp/fonts /tmp/shader /tmp/mscope.desktop /tmp/mscope.png /tmp/mscope.service"
rm -f /tmp/mscope.desktop /tmp/mscope.service /tmp/mscope-launcher

echo "✅ Deployment completed successfully!"
echo ""
echo "📋 Installation Summary:"
echo "  • Executable: $INSTALL_DIR/mscope"
echo "  • Desktop shortcut: /usr/share/applications/mscope.desktop"
echo "  • Systemd service: /etc/systemd/system/mscope.service"
echo "  • Launcher script: /usr/local/bin/mscope-launcher"
echo ""
echo "🚀 Usage:"
echo "  • Desktop: Launch from Applications menu"
echo "  • Terminal: mscope-launcher"
echo "  • Service: sudo systemctl start mscope"
echo "  • Auto-start: sudo systemctl enable mscope"
echo ""
echo "🔧 Optional: Enable auto-start on boot"
echo "  ssh $RPI_HOST 'sudo systemctl enable mscope'" 