# mscope for Raspberry Pi - Simple Installation

## 🚀 Quick Install (One Command)

```bash
curl -sSL https://raw.githubusercontent.com/arturodlrios/mscope/main/install-raspberry-pi.sh | bash
```

That's it! 🎉

## 📋 Manual Installation (Alternative)

If the one-command install doesn't work, you can install manually:

### 1. Download the latest release
```bash
# Get the latest version
LATEST_VERSION=$(curl -s https://api.github.com/repos/arturodlrios/mscope/releases/latest | grep '"tag_name"' | cut -d'"' -f4)
wget https://github.com/arturodlrios/mscope/releases/download/$LATEST_VERSION/mscope-arm64-$(date +%Y%m%d).tar.gz
```

### 2. Extract and install
```bash
tar xzf mscope-arm64-*.tar.gz
cd mscope-arm64-package
chmod +x install.sh
./install.sh
```

## 🎯 How to Launch

After installation, you can launch mscope in several ways:

- **Applications Menu**: Look for "mscope" in your Applications menu
- **Terminal**: Run `mscope-launcher`
- **Direct**: `cd /usr/local/bin/mscope && ./mscope`

## 🔧 What Gets Installed

- ✅ Pre-built ARM64 binary optimized for Raspberry Pi
- ✅ OpenGL ES 2.0 compatible graphics
- ✅ All required dependencies
- ✅ Desktop shortcut
- ✅ Launcher script

## 📊 Features

- Real-time serial data visualization
- Multiple graph types (line, scatter, bar)
- CSV data recording
- Modern GUI interface
- Optimized for Raspberry Pi performance

## 🐛 Troubleshooting

### "Permission denied" errors
```bash
sudo chmod +x /usr/local/bin/mscope-launcher
```

### "Could not load font file" error
```bash
sudo chown -R $USER:$USER /usr/local/bin/mscope/fonts
```

### Display issues
```bash
export DISPLAY=:0
mscope-launcher
```

## 📞 Support

- **GitHub Issues**: https://github.com/arturodlrios/mscope/issues
- **Documentation**: https://github.com/arturodlrios/mscope
- **Releases**: https://github.com/arturodlrios/mscope/releases

---

**Requirements**: Raspberry Pi (ARM64), Raspberry Pi OS, OpenGL ES 2.0 support 