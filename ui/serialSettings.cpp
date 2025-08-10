/** @file      serialSettings.cpp
 *  @brief     Source file for the serial settings functions.
 *  @author    arturodlr
 *  @date      Created on 2024/07/06
 *
 *  This software is the exclusive property of Cortx and is provided
 *  under strict confidentiality. It is intended for use solely by authorized
 *  personnel of Cortx and is protected by intellectual property laws.
 *  Unauthorized use, reproduction, or distribution in whole or in part is
 * strictly prohibited.
 *
 *  COPYRIGHT NOTICE: 2025 Cortx, Montreal, QC. All rights reserved.
 */

#include "../backends/imgui.h"
#include "../backends/implot.h"
#include <vector>
#include <string>
#include "../serial/serialComms.h"
#include "../pch/pch.h"
#include "dataReceptionSettings.h"

// Raspberry Pi (Linux) includes
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h> // For S_ISCHR
#include <dirent.h>   // For opendir, readdir, closedir
#include <cstring>

typedef enum
{
  BR_110 = 110,
  BR_300 = 300,
  BR_600 = 600,
  BR_1200 = 1200,
  BR_2400 = 2400,
  BR_4800 = 4800,
  BR_9600 = 9600,
  BR_14400 = 14400,
  BR_19200 = 19200,
  BR_38400 = 38400,
  BR_57600 = 57600,
  BR_115200 = 115200,
  BR_128000 = 128000,
  BR_256000 = 256000
} BaudRate_t;

typedef enum
{
  NO_PARITY = 0,   // No parity
  ODD_PARITY = 1,  // Odd parity
  EVEN_PARITY = 2, // Even parity
  MARK_PARITY = 3, // Mark parity
  SPACE_PARITY = 4 // Space parity
} Parity_t;

typedef enum
{
  ONE_SB = 0,
  ONE5_SB = 1,
  TWO_SB = 2
} StopBitSetting_t;

#define MAX_COM_PORT_NUM (256)

/* Flag to track if port has been opened */
bool portOpened = false;
bool errorInSerialReadings = false;

static std::vector<std::string> prv_getAvailableCOMPorts(void)
{
  std::vector<std::string> comPorts;

  // Define the base directory where serial ports are located
  const std::string devDir = "/dev";
  const std::string prefix = "tty";

  // Open the /dev directory
  DIR *dir = opendir(devDir.c_str());
  if (dir == nullptr)
  {
    std::cerr << "Error opening directory: " << devDir << std::endl;
    return comPorts;
  }

  struct dirent *entry;
  while ((entry = readdir(dir)) != nullptr)
  {
    std::string filename = entry->d_name;

    // Check if the file is a serial port
    if (filename.compare(0, prefix.size(), prefix) == 0)
    {
      std::string fullPath = devDir + "/" + filename;

      // Check if it's a character device
      struct stat fileStat;
      if (stat(fullPath.c_str(), &fileStat) == 0 && S_ISCHR(fileStat.st_mode))
      {
        comPorts.push_back(filename);
      }
    }
  }

  closedir(dir);

  return comPorts;
}

static OrbCode_t prv_selectPortNumber(std::string *pComPort)
{
  /* Drop-down menu for available COM ports */
  std::vector<std::string> comPorts = prv_getAvailableCOMPorts();
  static int selectedComPortIndex = 0;
  if (!comPorts.empty())
  {
    std::vector<const char *> comPortNames;
    for (const auto &port : comPorts)
    {
      comPortNames.push_back(port.c_str());
    }

    ImGui::Combo("COM Port", &selectedComPortIndex, comPortNames.data(),
                 static_cast<int>(comPortNames.size()));
    *pComPort = comPorts[selectedComPortIndex];
  }
  else
  {
    ImGui::Text("No COM ports available.");
    return NotAvailable;
  }
  return Success;
}

static void prv_selectBaudRate(uint32_t *pBaudRate)
{
  const char *baudRates[] = {"9600", "19200", "38400", "57600", "115200"};
  static int baudRateIndex = 0;

  /* Drop-down menu for baud rate */
  if (ImGui::Combo("Baud Rate", &baudRateIndex, baudRates,
                   IM_ARRAYSIZE(baudRates)))
  {
    if (baudRateIndex >= 0 && baudRateIndex < IM_ARRAYSIZE(baudRates))
    {
      switch (baudRateIndex)
      {
        case 0:
          *pBaudRate = BR_9600;
          break;
        case 1:
          *pBaudRate = BR_19200;
          break;
        case 2:
          *pBaudRate = BR_38400;
          break;
        case 3:
          *pBaudRate = BR_57600;
          break;
        case 4:
          *pBaudRate = BR_115200;
          break;
      }
    }
  }
}

static void prv_selectParity(uint8_t *pParity)
{
  const char *parityOptions[] = {"None", "Even", "Odd"};
  static int parityIndex = 0;

  /* Drop-down menu for parity */
  if (ImGui::Combo("Parity", &parityIndex, parityOptions,
                   IM_ARRAYSIZE(parityOptions)))
  {
    if (parityIndex >= 0 && parityIndex < IM_ARRAYSIZE(parityOptions))
    {
      switch (parityIndex)
      {
        case 0:
          *pParity = NO_PARITY;
          break;
        case 1:
          *pParity = EVEN_PARITY;
          break;
        case 2:
          *pParity = ODD_PARITY;
          break;
      }
    }
  }
}

static void prv_selectStopBits(uint8_t *pStopBits)
{
  const char *stopBitsOptions[] = {"1", "1.5", "2"};
  static int stopBitsIndex = 0;

  /* Drop-down menu for stop bits */
  if (ImGui::Combo("Stop Bits", &stopBitsIndex, stopBitsOptions,
                   IM_ARRAYSIZE(stopBitsOptions)))
  {
    if (stopBitsIndex >= 0 && stopBitsIndex < IM_ARRAYSIZE(stopBitsOptions))
    {
      switch (stopBitsIndex)
      {
        case 0:
          *pStopBits = ONE_SB;
          break;
        case 1:
          *pStopBits = ONE5_SB;
          break;
        case 2:
          *pStopBits = TWO_SB;
          break;
      }
    }
  }
}

OrbCode_t prv_configurePort(std::string *pComPort, uint32_t *pBaudRate,
                            uint8_t *pStopBits, uint8_t *pParity)
{
  OrbCode_t portNumCode = Success;

  portNumCode = prv_selectPortNumber(pComPort);

  prv_selectBaudRate(pBaudRate);
  prv_selectStopBits(pStopBits);
  prv_selectParity(pParity);

  return portNumCode;
}

void prv_managePort(std::string *pComPort, uint32_t *pBaudRate,
                    uint8_t *pStopBits, uint8_t *pParity,
                    OrbCode_t *pPortNumCode)
{
  static OrbCode_t openComCode = Success;

  if (portOpened)
  {
    if (ImGui::Button("Close COM Port"))
    {
      portOpened = false;
      closeCOMPort();
    }
    else if (errorInSerialReadings)
    {
      portOpened = false;
      closeCOMPort();
    }
  }
  else
  {
    if (*pPortNumCode == Success)
    {
      if (errorInSerialReadings)
      {
        ImGui::Text("Error while trying to read.");
      }
      // Check if channels are configured before allowing port opening
      int numChannels = getNumberOfChannels();
      if (numChannels <= 0)
      {
        ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.0f, 1.0f), 
                          "Please configure number of channels in 'Data Reception Settings' first");
        ImGui::BeginDisabled();
        ImGui::Button("Open COM Port");
        ImGui::EndDisabled();
      }
      else
      {
      if (ImGui::Button("Open COM Port"))
      {
        openComCode = openCOMPort(*pComPort, *pBaudRate, *pStopBits, *pParity);
        if (openComCode == Success)
        {
          portOpened = true;
          errorInSerialReadings = false;
        }
      }
        
        if (openComCode == OpenError)
      {
        ImGui::Text("Failed to open serial port");
      }
      else if (openComCode == PortStateError)
      {
        ImGui::Text("Error setting serial port state");
        }
      }
    }
  }
}

void serialReadingsError(void)
{
  errorInSerialReadings = true;
}

bool isSerialPortOpened(void)
{
  return portOpened;
}

void serialComSettings(void)
{
  OrbCode_t portNumCode = Success;
  static uint32_t baudRate
      = BR_9600; /* Default to 9600 if index out of bounds */
  static uint8_t parity
      = NO_PARITY; /* Default to no parity if index out of bounds */
  static uint8_t stopBits
      = ONE_SB; /* Default to 1 stop bit if index out of bounds */
  std::string comPort;

  if (ImGui::CollapsingHeader("Serial Communication Settings",
                              ImGuiTreeNodeFlags_DefaultOpen))
  {
    if (!portOpened)
      portNumCode = prv_configurePort(&comPort, &baudRate, &stopBits, &parity);

    prv_managePort(&comPort, &baudRate, &stopBits, &parity, &portNumCode);
  }
}
