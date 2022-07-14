#include <Arduino.h>

String Build_HTML(String Temperature, String Humidity);
String Page0_SelectMode_HTML(int OPERATING_MODE);
String Page1_DeviceName_HTML(String TextBox_Value);
String Page2_Monitoring_Type_HTML(void);
String Page2A_Temperature_Mode_HTML(int Temperature_Type);
String Page2B_Humidity_Mode_HTML(int Humidity_Type);
String Page2C_Combined_Mode_HTML(int Temperature_Type, int Humidity_Type);
String Page2D_Temperature_Thresholds_HTML(int Temperature_Type, float High_Temperature_Threshold, float Low_Temperature_Threshold);
String Page3_Sleep_Time_HTML(String Timer_Value);
String Page4_Contact_HTML(String Contact_Link);
String Page5_Review_HTML(String Device_Name, String High_Temp_Threshold, int Sleep_Time, String Contact_Link);
String Page6_Complete_HTML(String WiFi_Name);