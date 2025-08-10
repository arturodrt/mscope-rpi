# CI/CD Setup for mscope RPi Installer

This repository is configured with GitHub Actions to automatically build and release the mscope RPi installer.

## 🚀 Automated Build Process

### What happens automatically:

1. **On Push to Main**: Builds and tests the installer
2. **On Tag Creation**: Creates a GitHub release with the installer
3. **On Pull Request**: Builds and tests for validation

### Files Created:

- `.github/workflows/build-installer.yml` - GitHub Actions workflow
- `Dockerfile` - Multi-stage build for ARM64 cross-compilation
- `.dockerignore` - Excludes unnecessary files from Docker build
- `build-installer-local.sh` - Local testing script

## 🔧 Local Testing

To test the CI/CD process locally:

```bash
# Make sure Docker is installed and running
./build-installer-local.sh
```

This will:
1. Build the Docker image for ARM64
2. Extract the binary and assets
3. Create the installer package
4. Show the contents for verification

## 📦 Release Process

To create a new release:

1. **Update version** in your code
2. **Create and push a tag**:
   ```bash
   git tag v1.0.1
   git push origin v1.0.1
   ```
3. **GitHub Actions will automatically**:
   - Build the ARM64 binary
   - Create the installer package
   - Create a GitHub release
   - Upload the installer as a release asset

## 🔒 Security Features

- ✅ **No source code exposure** - Only compiled binary and assets
- ✅ **Cross-compilation** - Built for ARM64 without physical RPi
- ✅ **Reproducible builds** - Docker ensures consistent builds
- ✅ **Automated testing** - Validates installer creation

## 📋 Installer Contents

The generated installer contains:
- `mscope` - Compiled ARM64 binary
- `fonts/` - OpenSans and FontAwesome fonts
- `shader/` - Compiled shader files (no source code)
- `install.sh` - Installation script
- `uninstall-mscope.sh` - Uninstallation script
- `README.md` - Installation instructions
- `mscope.png` - Application icon

## 🎯 Benefits

- **No RPi needed** for installer generation
- **Automated releases** on GitHub
- **Consistent builds** across environments
- **Secure distribution** (no source code)
- **Easy deployment** to cortxtech.com

## 🔄 Workflow

1. **Develop** → Push to main branch
2. **Test** → GitHub Actions builds and tests
3. **Release** → Create tag for automatic release
4. **Distribute** → Download from GitHub releases

Your installer will be automatically generated and ready for distribution! 🚀 