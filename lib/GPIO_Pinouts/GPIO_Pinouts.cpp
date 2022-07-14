#include "GPIO_Pinouts.h"
#include <Arduino.h>
#include "LED_Control_Library.h"

void Define_Pins(void){
  //pinMode(RED_LED,        OUTPUT);
  //pinMode(GREEN_LED,      OUTPUT);
  //pinMode(BLUE_LED,       OUTPUT);
  Setup_LED_Outputs();
  pinMode(BATTERY_ENABLE, OUTPUT);
  pinMode(AUX_ENABLE,     INPUT);   //Although this is a control circuit, setting it as an input will force the IO Multiplexer to completely disconnect it when not in use.
  pinMode(BoardID_1,      INPUT);
  pinMode(BoardID_2,      INPUT);
  pinMode(V_BATT,         INPUT);
}

void Activate_AUX_Power(void){
  pinMode(AUX_ENABLE, OUTPUT);
  digitalWrite(AUX_ENABLE, LOW);
  delay(500);
}

void Deactivate_AUX_Power(void){
  pinMode(AUX_ENABLE, INPUT);
}