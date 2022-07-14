#include <Arduino.h>
#include <GPIO_Pinouts.h>

float Measure_Battery(void){
  //Activate the battery measurement circuit.
  //The battery measurements are routed through a 50/50 voltage divider, so the readings will be HALF of the actual voltage.
  //Readings are being taken by the onboard 12-bit ADC which will return readings from 0 @ 0[V] to 2^12 = 4096 @ Vref which is 3.3[V].
  float battery_sample = 0.0;
  digitalWrite(BATTERY_ENABLE, HIGH);       //Enable the battery measurement circuit
  delay(10);                                //Allow a short settling time for the captured voltage to stabilize
  for (int i=0; i<20; i++){
    battery_sample += analogRead(V_BATT);   //Take twenty samples of the captured battery voltage and sum them all together
    delay(1);                               //Short wait between samples
  }
  digitalWrite(BATTERY_ENABLE, LOW);                //Disable the battery measurement circuit.
  battery_sample = battery_sample / 20;             //Average = sum / number of samples
  battery_sample = 2 * 3.3 * battery_sample / 4096; //Calculate the actual voltage of the battery
  Serial.print("Battery Voltage = ");
  Serial.println(battery_sample, 3);
  digitalWrite(BATTERY_ENABLE, LOW);                //Disable the battery measurement circuit.
  return battery_sample;
}