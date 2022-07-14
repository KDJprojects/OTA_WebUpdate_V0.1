#include <Arduino.h>
#include <esp.h>
#include "GPIO_Pinouts.h"
#define Us_S_Factor 1000000
#define CONFIG_BUTTON_BITMASK GPIO_SEL_26
#define HELP_BUTTON_BITMASK GPIO_SEL_32
#define RED_LED_BITMASK GPIO_NUM_25



void Start_Timer_Sleep(int SECONDS){
  Serial.print("Going back to sleep for ");
  Serial.print(SECONDS / 60);
  Serial.println(" minutes or until woken by the button/reset.");
  esp_sleep_enable_timer_wakeup(SECONDS * Us_S_Factor);
  esp_deep_sleep_start();
}

void Low_Battery_Sleep(int SECONDS){
  Serial.println("Starting Low Battery Sleep");
  ledcDetachPin(RED_LED);
  pinMode(RED_LED, OUTPUT);
  Serial.println("Attempting to set the RED Led ON");
  digitalWrite(RED_LED, HIGH);
  delay(1000);
  gpio_hold_en(RED_LED_BITMASK);
  gpio_deep_sleep_hold_en();
  Start_Timer_Sleep(SECONDS);
}

void Start_Button_Sleep(void){
  Serial.print("Going back to sleep until woken up by ");
  Serial.println("GPIO (X)");
  esp_sleep_enable_ext1_wakeup(HELP_BUTTON_BITMASK, ESP_EXT1_WAKEUP_ANY_HIGH);
  esp_deep_sleep_start();
}


int Get_Wakeup_Cause(void){
    int CAUSE = 0;
    esp_sleep_wakeup_cause_t wakeup_reason;
    wakeup_reason = esp_sleep_get_wakeup_cause();

    if (wakeup_reason == ESP_SLEEP_WAKEUP_TIMER){
        Serial.println("Woken by Timer.");
        CAUSE = 1;
    }

    if (wakeup_reason == ESP_SLEEP_WAKEUP_EXT1){
        unsigned int WHICH_BUTTON = esp_sleep_get_ext1_wakeup_status();
        WHICH_BUTTON = (log(WHICH_BUTTON)/log(2));
        Serial.print("Woken by GPIO ");
        Serial.println(WHICH_BUTTON);
        CAUSE = WHICH_BUTTON;
    }
    return CAUSE;
}