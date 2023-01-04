/**
 * This software is distributed under the terms of the MIT License.
 * Copyright (c) 2022 LXRobotics.
 * Author: Bernhard Mayer <bernhard@generationmake.de>
 * Contributors: https://github.com/107-systems/107-Arduino-APDS-9950/graphs/contributors.
 */

#ifndef ARDUINO_APDS_9950_APDS_9950_CONST_H_
#define ARDUINO_APDS_9950_APDS_9950_CONST_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <stdint.h>

#include <type_traits>

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace APDS_9950
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

enum class Register : uint8_t
{
  APDS_9950_ENABLE            = 0x00,
  APDS_9950_ATIME             = 0x01,
  APDS_9950_WTIME             = 0x03,
  APDS_9950_AILTL             = 0x04,
  APDS_9950_AILTH             = 0x05,
  APDS_9950_AIHTL             = 0x06,
  APDS_9950_AIHTH             = 0x07,
  APDS_9950_PILTL             = 0x08,
  APDS_9950_PILTH             = 0x09,
  APDS_9950_PIHTL             = 0x0A,
  APDS_9950_PIHTH             = 0x0B,
  APDS_9950_PERS              = 0x0C,
  APDS_9950_CONFIG            = 0x0D,
  APDS_9950_PPULSE            = 0x0E,
  APDS_9950_CONTROL           = 0x0F,
  APDS_9950_ID                = 0x12,
  APDS_9950_STATUS            = 0x13,
  APDS_9950_CDATAL            = 0x14,
  APDS_9950_CDATAH            = 0x15,
  APDS_9950_RDATAL            = 0x16,
  APDS_9950_RDATAH            = 0x17,
  APDS_9950_GDATAL            = 0x18,
  APDS_9950_GDATAH            = 0x19,
  APDS_9950_BDATAL            = 0x1A,
  APDS_9950_BDATAH            = 0x1B,
  APDS_9950_PDATAL            = 0x1C,
  APDS_9950_PDATAH            = 0x1D,
};

enum class Error : int
{
  None    =  0,
  Timeout = -1,
  ChipId  = -2,
  Param   = -3,
};

/**************************************************************************************
 * CONSTANTS
 **************************************************************************************/

static uint8_t constexpr ID_EXPECTED_ID = 0x69;
static uint8_t constexpr DEFAULT_I2C_ADDR = 0x39;

/**************************************************************************************
 * CONVERSION FUNCTIONS
 **************************************************************************************/

template <typename Enumeration>
constexpr auto to_integer(Enumeration const value) -> typename std::underlying_type<Enumeration>::type
{
  return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

template <typename Enumeration>
constexpr auto bp(Enumeration const value) -> typename std::underlying_type<Enumeration>::type
{
  return to_integer(value);
}

template <typename Enumeration>
constexpr auto bm(Enumeration const value) -> typename std::underlying_type<Enumeration>::type
{
  return (1 << to_integer(value));
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* APDS_9950 */

#endif /* ARDUINO_APDS_9950_APDS_9950_CONST_H_ */
