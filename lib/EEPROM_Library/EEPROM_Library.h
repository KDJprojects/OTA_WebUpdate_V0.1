#include <Arduino.h>

String Load_TOKEN(void);
void Save_TOKEN(String NEW_TOKEN);
int Get_Reset_Count(void);
void Save_Reset_Count(int COUNT);
void Save_Configuration(String Device_Name, float High_Temp_Threshold, int Sleep_Time, String Contact_Link);
void Load_Configuration(String &Device_Name, float &High_Temp_Threshold, int &Sleep_Time, String &Contact_Link);
int Load_Email_Status(void);
void Save_Email_Status(int SENT_ALREADY);
bool Load_Test_Email_Status(void);
void Save_Test_Email_Status(bool SENT_ONCE);