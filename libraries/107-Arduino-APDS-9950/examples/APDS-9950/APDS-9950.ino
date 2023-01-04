/**
 * @brief Basic example demonstrating usage of 107-Arduino-APDS-9950 library.
 */

/**************************************************************************************
 * INCLUDE
 **************************************************************************************/

#include <Wire.h>

#include <107-Arduino-APDS-9950.h>

/**************************************************************************************
 * FUNCTION DECLARATION
 **************************************************************************************/

void i2c_generic_write(uint8_t const i2c_slave_addr, uint8_t const reg_addr, uint8_t const * buf, uint8_t const num_bytes);
void i2c_generic_read (uint8_t const i2c_slave_addr, uint8_t const reg_addr, uint8_t       * buf, uint8_t const num_bytes);

/**************************************************************************************
 * GLOBAL VARIABLES
 **************************************************************************************/

ArduinoAPDS_9950 apds_9950(i2c_generic_write,
                       i2c_generic_read,
//                       delay,
                       APDS_9950::DEFAULT_I2C_ADDR);

/**************************************************************************************
 * SETUP/LOOP
 **************************************************************************************/

void setup()
{
  Serial.begin(9600);
  while(!Serial) { }

  /* Setup Wire access */
  Wire.begin();

  /* Configure TSL2550 with Extended Range */
  if (!apds_9950.begin())
  {
    Serial.print("ArduinoAPDS_9950::begin(...) failed, error code ");
    Serial.print((int)apds_9950.error());
    for(;;) { }
  }

  Serial.println("APDS_9950 OK");
}

void loop()
{
  ArduinoAPDS_9950::colorDataRaw color;
  ArduinoAPDS_9950::proximityDataRaw proximity;

  apds_9950.get_colorData(&color);
  Serial.print("Clear = ");
  Serial.println(color.clear);
  Serial.print("Red   = ");
  Serial.println(color.red);
  Serial.print("Green = ");
  Serial.println(color.green);
  Serial.print("Blue  = ");
  Serial.println(color.blue);
  Serial.println("");

  apds_9950.get_proximityData(&proximity);
  Serial.print("Proximity = ");
  Serial.println(proximity.distance);
  Serial.println("");

  delay(500);
}

/**************************************************************************************
 * FUNCTION DEFINITION
 **************************************************************************************/

void i2c_generic_write(uint8_t const i2c_slave_addr, uint8_t const reg_addr, uint8_t const * buf, uint8_t const num_bytes)
{
  Wire.beginTransmission(i2c_slave_addr);
  Wire.write(reg_addr);
  for(uint8_t bytes_written = 0; bytes_written < num_bytes; bytes_written++) {
    Wire.write(buf[bytes_written]);
  }
  Wire.endTransmission();
}

void i2c_generic_read(uint8_t const i2c_slave_addr, uint8_t const reg_addr, uint8_t * buf, uint8_t const num_bytes)
{
  Wire.beginTransmission(i2c_slave_addr);
  Wire.write(reg_addr);
  Wire.endTransmission();

  Wire.requestFrom(i2c_slave_addr, num_bytes);
  for(uint8_t bytes_read = 0; (bytes_read < num_bytes) && Wire.available(); bytes_read++) {
    buf[bytes_read] = Wire.read();
  }
}
