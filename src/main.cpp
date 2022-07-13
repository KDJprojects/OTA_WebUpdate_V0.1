#include <Arduino.h>

void setup() {
Serial.begin(115200);
}

void loop() {
Serial.println("Sucesfully Updated to V0.1");
delay(3000);
}