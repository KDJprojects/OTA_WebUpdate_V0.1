#include <Arduino.h>
#include "GPIO_Pinouts.h"

#define RED_FADE_FREQUENCY    5000
#define GREEN_FADE_FREQUENCY  8000
#define BLUE_FADE_FREQUENCY   10000
#define RED_FADE_CHANNEL      0
#define BLUE_FADE_CHANNEL     1
#define GREEN_FADE_CHANNEL    2
#define LED_FADE_RESOLUTION   8
#define FADE_DELAY_uS         2000
#define BLINK_DELAY           250
#define MAX_BRIGHTNESS        255

void Setup_LED_Outputs(void){
  ledcSetup(RED_FADE_CHANNEL, RED_FADE_FREQUENCY, LED_FADE_RESOLUTION);   //Configure the PWM parameters
  ledcSetup(BLUE_FADE_CHANNEL, BLUE_FADE_FREQUENCY, LED_FADE_RESOLUTION);   //Configure the PWM parameters
  ledcSetup(GREEN_FADE_CHANNEL, GREEN_FADE_FREQUENCY, LED_FADE_RESOLUTION);   //Configure the PWM parameters
  ledcAttachPin(RED_LED, RED_FADE_CHANNEL);   //Attach all LEDs to the PWM channel
  ledcAttachPin(BLUE_LED, BLUE_FADE_CHANNEL);
  ledcAttachPin(GREEN_LED, GREEN_FADE_CHANNEL);
}

void Fade_Delay(void){
  int CURRENT_TIME = micros();
  while(micros() < CURRENT_TIME + FADE_DELAY_uS);
}

void Blink_Delay(void){
  int CURRENT_TIME = millis();
  while(millis() < CURRENT_TIME + BLINK_DELAY);
}


void Set_Color(int Red_Brightness, int Blue_Brightness, int Green_Brightness){
    ledcWrite(RED_FADE_CHANNEL, Red_Brightness);
    ledcWrite(BLUE_FADE_CHANNEL, Blue_Brightness);
    ledcWrite(GREEN_FADE_CHANNEL, Green_Brightness);
}

void Blink_Color(int Red_Brightness, int Blue_Brightness, int Green_Brightness, int Blink_Time){
  Set_Color(Red_Brightness, Blue_Brightness, Green_Brightness);
  delay(Blink_Time);
  Set_Color(0, 0, 0);
}