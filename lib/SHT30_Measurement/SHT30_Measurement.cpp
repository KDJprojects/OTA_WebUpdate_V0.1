#include <Arduino.h>
#include "GPIO_Pinouts.h"
#include <Wire.h>

bool CRC_CHECK(uint8_t MSB, uint8_t LSB, uint8_t CRC){
  uint8_t crc = 0xFF;
  uint8_t i;
  crc ^=MSB;
    for (i=0; i<8; i++)
      crc = crc & 0x80 ? (crc << 1) ^ 0x31 : crc << 1;

  crc ^= LSB;
  for (i=0; i<8; i++)
        crc = crc & 0x80 ? (crc << 1) ^ 0x31 : crc << 1;

  if (crc==CRC){
    return true;
  }
  else{
    return false;
  }
}


void Measure_Temp_and_Humidity(float &TEMP, float &HUMIDITY){
  uint8_t MSB     = 0x2C;   //Using single-shot mode, set to "High Repeatability"
  uint8_t LSB     = 0x06;   //Using single-shot mode, set to "High Repeatability"
  uint8_t ADDRESS = 0x45;   //Default Address

  //Open the connection and set the sensor's operating mode
  Wire.begin(I2C_SDA, I2C_SCL);
  Wire.beginTransmission(ADDRESS);  //Start talking with the sensor
  Wire.write(MSB);                  //Set to Single-shot, high repetability mode
  Wire.write(LSB);
  Wire.endTransmission();           //Close connection

  //The sensor will already have taken a measurement and stored it onboard, retrieve it.
  Wire.requestFrom(ADDRESS, (uint8_t)6);
  uint8_t data[6];
  for (uint8_t i = 0; i<6; i++){
    data[i] = Wire.read();
  }

  if ((CRC_CHECK(data[0],data[1],data[2])) && (CRC_CHECK(data[3],data[4],data[5]))){
    uint16_t TemperatureRaw   = (data[0]<<8)+(data[1]<<0);
    uint16_t RelHumidityRaw   = (data[3]<<8)+(data[4]<<0);
    TEMP       = ((float) TemperatureRaw) * 0.00267033 - 45.0;
    HUMIDITY   = ((float) RelHumidityRaw) * 0.0015259;
    Serial.print("Temperature = ");
    Serial.println(TEMP, 2);
    Serial.print("Relative Humidity = ");
    Serial.println(HUMIDITY, 2);
  }
}