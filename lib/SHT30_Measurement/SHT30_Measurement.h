#include <Arduino.h>

bool CRC_CHECK(uint8_t MSB, uint8_t LSB, uint8_t CRC);
void Measure_Temp_and_Humidity(float &TEMP, float &HUMIDITY);