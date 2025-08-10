/** @file      serialComms.cpp
 *  @brief     Source file for Serial Communication functions.
 *  @author    arturodlrios
 *  @date      Created on 2024/02/29
 *
 *  This software is the exclusive property of Cortx and is provided
 *  under strict confidentiality. It is intended for use solely by authorized
 *  personnel of Cortx and is protected by intellectual property laws.
 *  Unauthorized use, reproduction, or distribution in whole or in part is
 * strictly prohibited.
 *
 *  COPYRIGHT NOTICE: 2025 Cortx, Montreal, QC. All rights reserved.
 */

#include "serialComms.h"
#include "circularBuffer.h"
#include "csvStorage.h"
#include "../ui/serialSettings.h"
#include "../ui/viewerSettings.h"
#include "../ui/dataReceptionSettings.h"
#include <thread>
#include <atomic>
#include <mutex>
#include "../ui/settings.h"
#include <chrono>
#include "../ui/serialTerminal.h"

// Raspberry Pi (Linux) includes
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <dirent.h>  // Include for directory functions
#include <algorithm> // Include for std::find
static int hSerial;

#define NUMBERS_TO_RECEIVE (256)

std::chrono::steady_clock::time_point startTime1
    = std::chrono::steady_clock::now();
std::atomic<bool> threadRunning{false};
std::mutex bufferMutex;

/* Strings to store received data */
std::string g_receivedData = "0";
std::string g_previousReceivedData = "0";
CircularBuffer<char> circularBuffer(NUMBERS_TO_RECEIVE);
std::vector<float> floatData;

std::vector<std::vector<float>> channelsData;
std::vector<float> xValues;

/**
 * @brief Adds a new value to the end of the float vector, ensuring it does not
 * exceed a maximum size.
 *
 * If adding the new value exceeds the maximum size of the vector, the oldest
 * elements are removed from the beginning.
 *
 * @param floatVector Reference to the vector of floats.
 * @param newValue The new float value to add to the vector.
 */
void prv_addToVector(std::vector<float> &floatVector, float newValue)
{
  /* Add new value to the end of the vector */
  floatVector.push_back(newValue);

  /* Check if vector size exceeds maxSize */
  if (floatVector.size() > viewerDataSize())
  {
    /* Calculate how many elements to erase (this will be the excess elements)
     */
    size_t elementsToRemove = floatVector.size() - viewerDataSize();

    /* Erase the oldest elements from the beginning of the vector */
    floatVector.erase(floatVector.begin(),
                      floatVector.begin() + elementsToRemove);
  }
}

void initializeChannelData(int numberOfChannels)
{
  channelsData.clear();
  if (numberOfChannels > 0)
  {
  channelsData.resize(numberOfChannels);
  }
}

void resetChannelsData()
{
  startTime1 = std::chrono::steady_clock::now();
  for (auto &channel : channelsData)
  {
    channel.clear();
  }
  xValues.clear();
}

// Raspberry Pi (Linux) implementation



OrbCode_t openCOMPort(const std::string &comPortName, uint32_t baudRate,
                      uint8_t stopBits, uint8_t parity)
{
  // Ensure the comPortName is prefixed with /dev/
  std::string devicePath = comPortName;
  if (devicePath.find("/dev/") != 0)
  {
    devicePath = "/dev/" + devicePath;
  }

  // Open the serial port
  hSerial = open(devicePath.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
  if (hSerial < 0)
  {
    std::cerr << "Error opening serial port: " << strerror(errno) << std::endl;
    return OpenError;
  }

  // Get current terminal attributes
  struct termios tty;
  if (tcgetattr(hSerial, &tty) != 0)
  {
    std::cerr << "Error getting serial port attributes: " << strerror(errno)
              << std::endl;
    close(hSerial);
    return PortStateError;
  }

  // Clear struct for new port settings
  memset(&tty, 0, sizeof(tty));

  // Set Baud Rate
  speed_t speed;
  switch (baudRate)
  {
    case 9600:
      speed = B9600;
      break;
    case 19200:
      speed = B19200;
      break;
    case 38400:
      speed = B38400;
      break;
    case 57600:
      speed = B57600;
      break;
    case 115200:
      speed = B115200;
      break;
    default:
      std::cerr << "Unsupported baud rate!" << std::endl;
      close(hSerial);
      return OpenError;
  }
  cfsetospeed(&tty, speed);
  cfsetispeed(&tty, speed);

  // Set the number of data bits
  tty.c_cflag &= ~CSIZE;
  tty.c_cflag |= CS8; // 8 data bits

  // Set parity
  if (parity == 0)
  {
    tty.c_cflag &= ~PARENB; // No parity
  }
  else if (parity == 1)
  {
    tty.c_cflag |= PARENB;  // Enable parity
    tty.c_cflag &= ~PARODD; // Even parity
  }
  else if (parity == 2)
  {
    tty.c_cflag |= (PARENB | PARODD); // Odd parity
  }

  // Set stop bits
  if (stopBits == 1)
  {
    tty.c_cflag &= ~CSTOPB; // 1 stop bit
  }
  else if (stopBits == 2)
  {
    tty.c_cflag |= CSTOPB; // 2 stop bits
  }

  tty.c_cflag
      |= CREAD | CLOCAL; // Enable receiver and ignore modem control lines

  // Set the timeout options
  tty.c_cc[VTIME] = 0; // No timeout
  tty.c_cc[VMIN] = 0;  // Non-blocking read

  // Apply the configuration
  if (tcsetattr(hSerial, TCSANOW, &tty) != 0)
  {
    std::cerr << "Error setting serial port attributes: " << strerror(errno)
              << std::endl;
    close(hSerial);
    return PortStateError;
  }

  return Success;
}

void closeCOMPort(void)
{
  close(hSerial);
}

OrbCode_t readSerialData(void)
{
  char buffer[64];
  ssize_t bytesRead;
  char currentChar;
  static bool startFlag = false;
  int numberOfChannels = 0;
  std::lock_guard<std::mutex> lock(bufferMutex);

  numberOfChannels = getNumberOfChannels();

  // Initialize channelData if it hasn't been done or if the number of channels
  // has changed
  if (channelsData.size() != numberOfChannels)
  {
    initializeChannelData(numberOfChannels);
  }

  /* Read data from the serial port */
  if (isSerialPortOpened())
  {
    bytesRead = read(hSerial, buffer, sizeof(buffer));
    if (bytesRead > 0)
    {
      /* Push data into circular buffer */
      for (ssize_t i = 0; i < bytesRead; ++i)
      {
        currentChar = buffer[i];

        /* Check if the character is a numerical digit */
        if (currentChar > 0)
        {
          /* Push each character into the circular buffer */
          circularBuffer.push(currentChar);
        }
        else
        {
          return InvalidData;
        }
      }
    }
    else if (bytesRead < 0)
    {
      // Handle read error
      return ReadError;
    }

    /* Process data from circular buffer */
    while (!circularBuffer.isEmpty())
    {
      /* Pop character from circular buffer */
      currentChar = circularBuffer.pop();
      if (!startFlag && currentChar == '\n')
      {
        startFlag = true;
        g_receivedData.clear(); /* Clear the buffer for the next data */
        floatData.clear();
      }

      if (startFlag && currentChar == '\r')
      {
        /* End of line, store the received data */
        float newData = std::stof(g_receivedData);
        floatData.push_back(newData);
        startFlag = false;

        if (floatData.size() == numberOfChannels && numberOfChannels > 0)
        {
          for (int currentChannel = 0; currentChannel < numberOfChannels;
               currentChannel++)
          {
            if (currentChannel < channelsData.size())
          {
            prv_addToVector(channelsData[currentChannel],
                            floatData[currentChannel]);
            }
          }

          std::chrono::steady_clock::time_point now
              = std::chrono::steady_clock::now();
          double elapsedTime
              = std::chrono::duration_cast<std::chrono::milliseconds>(
                    now - startTime1)
                    .count()
                / 1000.0; // Convert to seconds
          prv_addToVector(xValues, static_cast<float>(elapsedTime));

          // Write data to CSV if recording is active
          if (isCSVRecording())
          {
            writeCSVDataRow(elapsedTime, floatData);
          }
        }

        return DataReceived;
      }

      if (startFlag && currentChar == ',')
      {
        try
        {
          float newData = std::stof(g_receivedData);
          floatData.push_back(newData);
        }
        catch (const std::invalid_argument &e)
        {
          // Handle error: Received data contains non-numeric characters
        }
        catch (const std::out_of_range &e)
        {
          // Handle error: The value represented by the string is out of range
        }
        g_receivedData.clear(); /* Clear the buffer for the next data */
      }

      /* Check if the character is a digit, dot, or minus sign */
      if (startFlag
          && (isdigit(currentChar) || currentChar == '.' || currentChar == '-'))
      {
        /* Append the digit to the received data string */
        g_receivedData += currentChar;
      }
    }
  }
  else
  {
    resetChannelsData();
  }

  return Success;
}

void startSerialThread(void)
{
  threadRunning = true;
  while (threadRunning)
  {
    if (!isDataReceptionPaused())
    {
      readSerialData();
    }
    
    // Add sleep to prevent excessive CPU usage
    std::this_thread::sleep_for(std::chrono::milliseconds(10)); // 10ms sleep = 100Hz polling
  }
}

void endSerialThread(void)
{
  threadRunning = false;
}
