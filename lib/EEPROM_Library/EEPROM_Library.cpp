#include <Arduino.h>
#include <Preferences.h>

Preferences preferences;

String Load_TOKEN(void){
    preferences.begin("AUTH_TOKEN", false);
    String TOKEN = preferences.getString("TOKEN", "");
    preferences.end();
    return TOKEN;
}

void Save_TOKEN(String NEW_TOKEN){
    preferences.begin("AUTH_TOKEN", false);
    preferences.putString("TOKEN", NEW_TOKEN);
    preferences.end();
}

int Get_Reset_Count(void){
    preferences.begin("RESET_COUNT", false);
    int INTERRUPTED_CYCLE_COUNT = preferences.getInt("COUNTER", 0);
    preferences.end();
    return INTERRUPTED_CYCLE_COUNT;
}

void Save_Reset_Count(int COUNT){
    preferences.begin("RESET_COUNT", false);
    preferences.putInt("COUNTER", COUNT);
    preferences.end();
}

void Save_Configuration(String Device_Name, float High_Temp_Threshold, int Sleep_Time, String Contact_Link){
    preferences.begin("CONFIG", false);
    preferences.putString("NAME", Device_Name);
    preferences.putFloat("HIGHTEMP", High_Temp_Threshold);
    preferences.putInt("SLEEPTIME", Sleep_Time);
    preferences.putString("CONTACT", Contact_Link);
    preferences.end();
}

void Load_Configuration(String &Device_Name, float &High_Temp_Threshold, int &Sleep_Time, String &Contact_Link){
    preferences.begin("CONFIG", false);
    Device_Name = preferences.getString("NAME", "");
    High_Temp_Threshold = preferences.getFloat("HIGHTEMP", 0.0);
    Sleep_Time = preferences.getInt("SLEEPTIME", 0);
    Contact_Link = preferences.getString("CONTACT", "");
    preferences.end();
}

void Save_Email_Status(int SENT_ALREADY){
    preferences.begin("EMAIL", false);
    preferences.putInt("SENT", SENT_ALREADY);
    preferences.end();
}

int Load_Email_Status(void){
    int SENT_EMAILS = 0;
    preferences.begin("EMAIL", false);
    SENT_EMAILS = preferences.getInt("SENT", 0);
    preferences.end();
    return SENT_EMAILS;
}

bool Load_Test_Email_Status(void){
    bool SENT_BEFORE = 1;
    preferences.begin("TEST", false);
    SENT_BEFORE = preferences.getBool("SENT_ONCE", 0);
    preferences.end();
    return SENT_BEFORE;
}

void Save_Test_Email_Status(bool SENT_ONCE){
    preferences.begin("TEST", false);
    preferences.putBool("SENT_ONCE", SENT_ONCE);
    preferences.end();
}