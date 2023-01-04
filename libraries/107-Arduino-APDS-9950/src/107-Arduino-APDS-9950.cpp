/**
 * This software is distributed under the terms of the MIT License.
 * Copyright (c) 2022 LXRobotics.
 * Author: Bernhard Mayer <bernhard@generationmake.de>
 * Contributors: https://github.com/107-systems/107-Arduino-APDS-9950/graphs/contributors.
 */

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include "107-Arduino-APDS-9950.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

using namespace APDS_9950;

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

ArduinoAPDS_9950::ArduinoAPDS_9950(APDS_9950::I2cWriteFunc write,
                               APDS_9950::I2cReadFunc read,
 //                              APDS_9950::DelayFunc delay,
                               uint8_t const i2c_slave_addr)
: _error{APDS_9950::Error::None}
, _io{write, read, i2c_slave_addr}
{
}


/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

bool ArduinoAPDS_9950::begin()
{
  /* Check the CHIP ID if it matches the expected value.
   */
  if (_io.read((Register const)((uint8_t)(APDS_9950::Register::APDS_9950_ID)|0x80)) != APDS_9950::ID_EXPECTED_ID) {
    _error = APDS_9950::Error::ChipId;
    return false;
  }

  _io.write((Register const)((uint8_t)(APDS_9950::Register::APDS_9950_WTIME)|0x80), 0xFF);   /* set WTIME to default value */
  _io.write((Register const)((uint8_t)(APDS_9950::Register::APDS_9950_ATIME)|0x80), 0xFF);   /* set ATIME to default value */
  _io.write((Register const)((uint8_t)(APDS_9950::Register::APDS_9950_PPULSE)|0x80), 0x0F);   /* set PPULSE to 15 */
  _io.write((Register const)((uint8_t)(APDS_9950::Register::APDS_9950_ENABLE)|0x80), 0x0F);   /* set WEN, PEN, AEN and PON bit in ENABLE */

  return true;
}

void ArduinoAPDS_9950::get_colorData(struct colorDataRaw * color)
{
  color->clear = _io.read16((Register const)((uint8_t)(APDS_9950::Register::APDS_9950_CDATAL)|0xA0));
  color->red   = _io.read16((Register const)((uint8_t)(APDS_9950::Register::APDS_9950_RDATAL)|0xA0));
  color->green = _io.read16((Register const)((uint8_t)(APDS_9950::Register::APDS_9950_GDATAL)|0xA0));
  color->blue  = _io.read16((Register const)((uint8_t)(APDS_9950::Register::APDS_9950_BDATAL)|0xA0));
}

void ArduinoAPDS_9950::get_proximityData(struct proximityDataRaw * proximity)
{
  proximity->distance = _io.read16((Register const)((uint8_t)(APDS_9950::Register::APDS_9950_PDATAL)|0xA0));
}

APDS_9950::Error ArduinoAPDS_9950::error()
{
  return _error;
}
