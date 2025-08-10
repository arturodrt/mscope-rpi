#!/bin/bash

set -e

echo "🗑️  Uninstalling mscope from Raspberry Pi..."

# Remove the main installation directory
if [ -d "/usr/local/bin/mscope" ]; then
    echo "📁 Removing /usr/local/bin/mscope..."
    sudo rm -rf /usr/local/bin/mscope
fi

# Remove the launcher script
if [ -f "/usr/local/bin/mscope-launcher" ]; then
    echo "🔗 Removing launcher script..."
    sudo rm -f /usr/local/bin/mscope-launcher
fi

# Remove desktop shortcut
if [ -f "/usr/share/applications/mscope.desktop" ]; then
    echo "🖥️  Removing desktop shortcut..."
    sudo rm -f /usr/share/applications/mscope.desktop
fi

# Remove icon
if [ -f "/usr/share/pixmaps/mscope.png" ]; then
    echo "🖼️  Removing icon..."
    sudo rm -f /usr/share/pixmaps/mscope.png
fi

# Remove any old installation paths (if they exist)
if [ -d "/usr/bin/mscope" ]; then
    echo "📁 Removing old /usr/bin/mscope..."
    sudo rm -rf /usr/bin/mscope
fi

if [ -d "/usr/bin/fonts" ]; then
    echo "📁 Removing old /usr/bin/fonts..."
    sudo rm -rf /usr/bin/fonts
fi

if [ -f "/usr/share/pixmaps/mscope.png" ]; then
    echo "🖼️  Removing old icon..."
    sudo rm -f /usr/share/pixmaps/mscope.png
fi

# Update desktop database
if command -v update-desktop-database >/dev/null 2>&1; then
    echo "🔄 Updating desktop database..."
    sudo update-desktop-database /usr/share/applications/ 2>/dev/null || true
fi

echo "✅ mscope has been completely uninstalled!"
echo "💡 Note: Dependencies were not removed. Run 'sudo apt autoremove' if you want to clean them up." 