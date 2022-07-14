#include <Arduino.h>
void Setup_LED_Outputs(void);  //Assign these GPIO Pins to 3 separate PWM channels, allowing a user full control over each LED.  The MAX Brightness and the delay between fade steps is defined in the Library.
void Fade_Delay(void);
void Blink_Delay(void);
void Set_Color(int Red_Brightness, int Blue_Brightness, int Green_Brightness);
void Blink_Color(int Red_Brightness, int Blue_Brightness, int Green_Brightness, int Blink_Time);
