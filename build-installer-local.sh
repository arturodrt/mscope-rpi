#!/bin/bash

# Local installer build script for testing CI/CD process
set -e

echo "🔨 Building mscope RPi installer locally..."

# Check if Docker is available
if ! command -v docker &> /dev/null; then
    echo "❌ Docker is required but not installed"
    exit 1
fi

# Build Docker image for ARM64
echo "🐳 Building Docker image for ARM64..."
docker build -t mscope-rpi:local .

# Create a container from the image
echo "📦 Creating container to extract files..."
docker create --name mscope-extract-local mscope-rpi:local

# Create installer directory
echo "📁 Creating installer directory..."
rm -rf mscope-rpi-fresh-local
mkdir -p mscope-rpi-fresh-local

# Copy binary from container
echo "📋 Copying binary..."
docker cp mscope-extract-local:/usr/local/bin/mscope/mscope ./mscope-rpi-fresh-local/

# Copy fonts from container
echo "📋 Copying fonts..."
docker cp mscope-extract-local:/usr/local/bin/mscope/fonts ./mscope-rpi-fresh-local/

# Copy shaders from container
echo "📋 Copying shaders..."
docker cp mscope-extract-local:/usr/local/bin/mscope/shader ./mscope-rpi-fresh-local/

# Copy installation files
echo "📋 Copying installation files..."
cp install.sh mscope-rpi-fresh-local/
cp uninstall-mscope.sh mscope-rpi-fresh-local/
cp README.md mscope-rpi-fresh-local/
cp deploy/icon.png mscope-rpi-fresh-local/mscope.png

# Make files executable
echo "🔧 Setting permissions..."
chmod +x mscope-rpi-fresh-local/mscope
chmod +x mscope-rpi-fresh-local/install.sh
chmod +x mscope-rpi-fresh-local/uninstall-mscope.sh

# Create installer package
echo "📦 Creating installer package..."
cd mscope-rpi-fresh-local
tar -czf ../mscope-rpi-installer-local.tar.gz *
cd ..

# Clean up
echo "🧹 Cleaning up..."
docker rm mscope-extract-local

echo "✅ Installer created: mscope-rpi-installer-local.tar.gz"
echo "📊 Package size: $(du -h mscope-rpi-installer-local.tar.gz | cut -f1)"
echo "📋 Contents:"
tar -tzf mscope-rpi-installer-local.tar.gz 