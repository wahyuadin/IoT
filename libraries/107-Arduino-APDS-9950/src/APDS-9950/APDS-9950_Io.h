/**
 * This software is distributed under the terms of the MIT License.
 * Copyright (c) 2022 LXRobotics.
 * Author: Bernhard Mayer <bernhard@generationmake.de>
 * Contributors: https://github.com/107-systems/107-Arduino-APDS-9950/graphs/contributors.
 */

#ifndef ARDUINO_APDS_9950_APDS_9950_IO_H_
#define ARDUINO_APDS_9950_APDS_9950_IO_H_

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#undef max
#undef min
#include <functional>

#include "APDS-9950_Const.h"

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

namespace APDS_9950
{

/**************************************************************************************
 * TYPEDEF
 **************************************************************************************/

typedef std::function<void(uint8_t const, uint8_t const, uint8_t const *, uint8_t const)> I2cWriteFunc;
typedef std::function<void(uint8_t const, uint8_t const, uint8_t       *, uint8_t const)> I2cReadFunc;

/**************************************************************************************
 * CLASS DECLARATION
 **************************************************************************************/

class APDS_9950_Io
{
public:

  APDS_9950_Io(I2cWriteFunc write, I2cReadFunc read, uint8_t const i2c_slave_addr);


  inline void set_i2c_slace_addr(uint8_t const i2c_slave_addr) { _i2c_slave_addr = i2c_slave_addr; }


  void    write   (Register const reg);
  uint8_t read    (Register const reg);
  uint16_t read16 (Register const reg);
  void    write   (Register const reg, uint8_t const val);
  void    read    (Register const reg, uint8_t * buf, size_t const bytes);
  void    write   (Register const reg, uint8_t const * buf, size_t const bytes);
  void    modify  (Register const reg, uint8_t const bitmask, uint8_t const val);
  bool    isBitSet(Register const reg, uint8_t const bitpos);


private:

  I2cWriteFunc _write;
  I2cReadFunc _read;

  uint8_t _i2c_slave_addr;
};

/**************************************************************************************
 * NAMESPACE
 **************************************************************************************/

} /* APDS_9950 */

#endif /* ARDUINO_APDS_9950_APDS_9950_IO_H_ */
