#ifndef BASICINTERFACE_HPP
#define BASICINTERFACE_HPP

#include "hwlib.hpp"

using hwlib::i2c_bus;

/// @file

/// \brief
/// Abstract accelerometer interface class
/// \details
/// This abstract class can be used to implement a I2C based accelerometer.
class accelerometer_interface {
 protected:
  i2c_bus& bus;     /// \brief Communication bus
  uint8_t address;  /// \brief I2C address on the bus

 public:
  /// \brief
  /// Constructor abstract class
  /// \details
  /// This constructor should be called in the initializer list of the class that implements this abstract class.
  accelerometer_interface(i2c_bus& bus, uint8_t address) : bus(bus), address(address) {}

  /// \brief
  /// Abstract function to get X-axis accelerometer data
  virtual int16_t getAccX() = 0;

  /// \brief
  /// Abstract function to get Y-axis accelerometer data
  virtual int16_t getAccY() = 0;

  /// \brief
  /// Abstract function to get Z-axis accelerometer data
  virtual int16_t getAccZ() = 0;

  /// \brief
  /// Abstract function to get angle of X-axis
  /// \details
  /// The angle can be calculated with the accelerometer data.
  virtual int getAngleX() = 0;

  /// \brief
  /// Abstract function to get angle of Y-axis
  /// \details
  /// The angle can be calculated with the accelerometer data.
  virtual int getAngleY() = 0;
};

#endif