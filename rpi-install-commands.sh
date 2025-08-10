#!/bin/bash
# Commands to run on Raspberry Pi for mscope fresh installation

echo "🚀 Starting mscope fresh installation process..."
echo ""

echo "📍 Step 1: Uninstalling existing mscope..."
chmod +x uninstall-mscope.sh
./uninstall-mscope.sh

echo ""
echo "📍 Step 2: Extracting fresh installer package..."
tar -xzf mscope-rpi-fresh-20250809.tar.gz

echo ""
echo "📍 Step 3: Installing fresh mscope..."
chmod +x install.sh
./install.sh

echo ""
echo "📍 Step 4: Testing installation..."
echo "Launching mscope in 3 seconds..."
sleep 3
mscope-launcher

echo ""
echo "✅ Process completed!"
echo "If mscope launched successfully, the installation is working correctly." 