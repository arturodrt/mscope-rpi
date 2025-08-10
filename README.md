# μscope for Raspberry Pi 5 - FIXED UI VERSION

Real-time data visualization and serial communication tool with **proper UI rendering**.

## 🚀 Quick Installation

1. **Download** `mscope-rpi5-package-FIXED.tar.gz` to your Raspberry Pi 5
2. **Extract and install:**
   ```bash
   tar -xzf mscope-rpi5-package-FIXED.tar.gz
   cd mscope-rpi5-release/
   ./install.sh
   ```

That's it! The installer will automatically:
- Install all required dependencies
- Set up μscope in the system
- Create desktop shortcuts
- Configure everything for you

## 🎯 Usage

**Run from command line:**
```bash
mscope-launcher
```

**Or find "mscope" in your Applications menu**

## 📊 Features

- **Real-time data visualization** with live plotting
- **Serial communication** support (USB/UART)
- **CSV data recording** with configurable channels  
- **Up to 3 data channels** (Lite version)
- **Modern UI** optimized for Raspberry Pi
- **✅ FIXED: Proper UI rendering** (no more gray window!)

## 📝 Notes

- **Raspberry Pi 5** with 64-bit OS recommended
- For serial access: `sudo usermod -a -G dialout $USER` (then logout/login)
- Connect your device to `/dev/ttyACM0` or configure in settings
- Data format: CSV (e.g., `1.23,4.56,7.89`)
- **✅ UI now renders properly** with OpenGL ES 2.0 compatible shaders

## 🔧 What's Fixed

- **UI Rendering**: Fixed GLSL shader version compatibility for OpenGL ES
- **ImGui Support**: Proper OpenGL ES 2.0 backend configuration
- **No More Gray Window**: UI elements now display correctly
- **All Features Working**: Settings, plotting, and controls fully functional

## 📋 System Requirements

- Raspberry Pi 5 (ARM64)
- Raspberry Pi OS (64-bit)
- Internet connection for dependency installation

---

**Version**: Raspberry Pi 5 Lite (3-channel) - UI FIXED  
**Architecture**: ARM64  
**Build Date**: $(date +%Y-%m-%d)
