# mscope for Raspberry Pi

Real-time serial data visualizer optimized for Raspberry Pi.

## Quick Installation

1. Extract this package to a directory
2. Open a terminal in that directory
3. Run the installer:

```bash
chmod +x install.sh
./install.sh
```

## What Gets Installed

- ✅ Pre-built ARM64 binary optimized for Raspberry Pi
- ✅ OpenGL ES 2.0 compatible graphics
- ✅ All required dependencies
- ✅ Desktop shortcut
- ✅ Launcher script

## How to Launch

After installation, you can launch mscope in several ways:

- **Applications Menu**: Look for "mscope" in your Applications menu
- **Terminal**: Run `mscope-launcher`
- **Direct**: `cd /usr/local/bin/mscope && ./mscope`

## Features

- Real-time serial data visualization
- Multiple graph types (line, scatter, bar)
- CSV data recording
- Modern GUI interface
- Optimized for Raspberry Pi performance

## Troubleshooting

### No Data Appearing?

If mscope launches but no data appears in the graphs:

1. **Check your serial device**: 
   ```bash
   ls -la /dev/tty*
   ```
   Common devices: `/dev/ttyACM0`, `/dev/ttyUSB0`, `/dev/ttyAMA0`

2. **Configure serial settings in mscope**:
   - Open mscope
   - Go to **Settings** → **Serial Communication**
   - Set the correct **Port** (e.g., `/dev/ttyACM0`)
   - Set the correct **Baud Rate** (e.g., 115200)
   - Click **Connect**

3. **Test serial data manually**:
   ```bash
   sudo apt install minicom
   sudo stty -F /dev/ttyACM0 115200
   timeout 5s sudo cat /dev/ttyACM0
   ```
   You should see data like: `-0.32857,-0.32915,-0.14576`

4. **Check permissions**:
   ```bash
   sudo usermod -a -G dialout $USER
   ```
   Then log out and back in.

## Requirements

- Raspberry Pi (ARM64)
- Raspberry Pi OS
- OpenGL ES 2.0 support

## Uninstall

To completely remove mscope from your system:

**Option 1: Use the included uninstall script**
```bash
chmod +x uninstall-mscope.sh
./uninstall-mscope.sh
```

**Option 2: Manual removal**
```bash
sudo rm -rf /usr/local/bin/mscope
sudo rm -f /usr/local/bin/mscope-launcher
sudo rm -f /usr/share/applications/mscope.desktop
sudo rm -f /usr/share/pixmaps/mscope.png
sudo update-desktop-database /usr/share/applications/
```

## Support

For support and more information, visit: https://cortxtech.com 