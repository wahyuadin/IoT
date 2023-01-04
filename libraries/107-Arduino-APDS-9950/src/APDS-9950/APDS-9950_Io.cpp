/**
 * This software is distributed under the terms of the MIT License.
 * Copyright (c) 2022 LXRobotics.
 * Author: Bernhard Mayer <bernhard@generationmake.de>
 * Contributors: https://github.com/107-systems/107-Arduino-APDS-9950/graphs/contributors.
 */

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include "APDS-9950_Io.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace APDS_9950
{

/**************************************************************************************
 * CTOR/DTOR
 **************************************************************************************/

APDS_9950_Io::APDS_9950_Io(I2cWriteFunc write, I2cReadFunc read, uint8_t const i2c_slave_addr)
: _write{write}
, _read{read}
, _i2c_slave_addr{i2c_slave_addr}
{

}

/**************************************************************************************
 * PUBLIC MEMBER FUNCTIONS
 **************************************************************************************/

uint8_t APDS_9950_Io::read(Register const reg)
{
  uint8_t data = 0;
  read(reg, &data, 1);
  return data;
}

void APDS_9950_Io::write(Register const reg)
{
  uint8_t const val=0;
  write(reg, &val, 0);
}

void APDS_9950_Io::write(Register const reg, uint8_t const val)
{
  write(reg, &val, 1);
}

void APDS_9950_Io::read(Register const reg, uint8_t * buf, size_t const bytes)
{
  _read(_i2c_slave_addr, to_integer(reg), buf, bytes);
}

uint16_t APDS_9950_Io::read16(Register const reg)
{
  uint16_t data = 0;
  read(reg, (uint8_t *)&data, 2);
  return data;
}

void APDS_9950_Io::write(Register const reg, uint8_t const * buf, size_t const bytes)
{
  _write(_i2c_slave_addr, to_integer(reg), buf, bytes);
}

void APDS_9950_Io::modify(Register const reg, uint8_t const bitmask, uint8_t const val)
{
  uint8_t reg_val = read(reg);
  reg_val &= ~(bitmask);
  reg_val |= (val & bitmask);
  write(reg, reg_val);
}

bool APDS_9950_Io::isBitSet(Register const reg, uint8_t const bitpos)
{
  uint8_t const reg_val = read(reg);
  if (reg_val & (1<<bitpos))
    return true;
  else
    return false;
}

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* APDS_9950 */
