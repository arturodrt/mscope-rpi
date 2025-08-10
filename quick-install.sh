#!/bin/bash

echo "🚀 mscope Quick Install for Raspberry Pi"
echo "========================================"

# Check if running on Raspberry Pi
if ! grep -q "Raspberry Pi" /proc/cpuinfo 2>/dev/null; then
    echo "❌ This installer is for Raspberry Pi only"
    exit 1
fi

# Download and run the full installer
echo "📥 Downloading installer..."
curl -sSL https://raw.githubusercontent.com/arturodlrios/mscope/main/install-raspberry-pi.sh | bash 