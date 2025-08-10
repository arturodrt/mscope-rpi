# mscope - Complete Feature List

## **🔧 Core Application Features**
- **Cross-platform compatibility** (Windows, macOS, Linux)
- **Real-time serial data visualization** from microcontrollers
- **Multi-threaded architecture** with separate serial communication thread
- **Modern OpenGL-based rendering** with ImGui/ImPlot integration
- **Dockable UI system** with resizable and rearrangeable windows

## **📡 Serial Communication Features**
- **Serial port configuration** with customizable settings:
  - Baud rate selection
  - Parity settings
  - Stop bits configuration
  - Port selection from available COM ports
- **Real-time serial data reception** with continuous monitoring
- **Serial terminal interface** for data logging and visualization
- **Error handling** for serial communication issues
- **Play/Stop controls** for data reception
- **Data reception pause/resume functionality**

## **📊 Data Visualization Features**
- **Multi-channel plotting** (supports up to 3 channels - Lite version)
- **Real-time graph updates** with live data streaming
- **Combined view** showing all channels on one plot
- **Individual channel plots** with separate windows (can be enabled/disabled)
- **Configurable data buffer size** (up to 10,000 elements)
- **Customizable channel names** for better identification
- **Interactive plotting** with zoom and pan capabilities
- **Channel visibility controls** (show/hide individual channels)
- **Auto-Fit Plot View** - Double-click to automatically fit all data points within the visible range

## **💾 Data Recording & Export Features**
- **CSV data recording** with automatic timestamping
- **Real-time CSV file writing** as data is received
- **Configurable CSV filename** (manual or automatic timestamped)
- **Channel name configuration** for CSV headers
- **Recording status display** (start/stop indicators)
- **Timestamp column** in CSV output (seconds from start)

## **⚙️ Configuration & Settings**
- **General settings panel** with theme selection (dark/light mode)
- **Serial communication settings** panel
- **Data reception settings** panel
- **CSV recording settings** panel
- **Viewer settings** panel for plot configuration
- **Channel configuration** with custom labels
- **Data size configuration** with range validation

## **🎨 User Interface Features**
- **Modern ImGui-based interface** with professional appearance
- **Custom font support** (OpenSans family + FontAwesome icons)
- **Dockable window system** for flexible layout
- **Collapsible settings sections** for organized configuration
- **Real-time status indicators** throughout the interface
- **Responsive design** that adapts to window resizing
- **Professional theming** with dark/light mode support

## **🔍 Data Processing Features**
- **Float data parsing** from serial input
- **Space-separated value format** support
- **Real-time data buffering** with configurable size limits
- **Multi-channel data separation** and processing
- **Circular buffer implementation** for efficient memory usage

## **📈 Statistics & Analysis Features**
- **Real-time channel statistics** display:
  - Minimum and maximum values
  - Average (mean) calculation
  - Data range calculation
  - Data point count
  - Time span measurement
- **Per-channel statistics** in individual plot windows

## **🛠️ Technical Features**
- **CMake build system** for cross-platform compilation
- **OpenGL 4.1+ rendering** with modern shader support
- **GLFW window management** for cross-platform compatibility
- **Thread-safe data handling** between serial and UI threads
- **Memory-efficient data structures** for large datasets
- **Error handling and validation** throughout the application

## **📁 File Management Features**
- **Automatic font discovery** from multiple possible locations
- **CSV file generation** with proper formatting
- **Timestamped file naming** for organized data storage
- **Cross-platform file path handling**

## **🎯 Professional Features**
- **Commercial licensing** with Cortx branding
- **Professional documentation** with comprehensive headers
- **Modular code architecture** for maintainability
- **Extensible design** for future feature additions
- **Performance optimization** for real-time applications

## **🎮 Interactive Plot Controls**
- **Mouse wheel zoom** in/out functionality
- **Click and drag** to pan around the plot
- **Right-click and drag** to zoom into specific areas
- **Double-click** for auto-fit plot view
- **Real-time plot interaction** while data is streaming

---

**Total Features: 50+** across 12 major categories

This comprehensive real-time data visualization tool is specifically designed for microcontroller development and debugging, with professional-grade features for data analysis, recording, and interactive visualization. 