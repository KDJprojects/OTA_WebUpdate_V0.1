#include <Arduino.h>
#include "RP_Logo.h"

String Build_HTML(String Temperature, String Humidity){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>Temperature & Humidity Sensor Demo</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 5px;} h1 {color: #444444;margin: 10px auto 20px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: inline-block;padding: 15px 25px;background-color: #3498db;border: none;color: black;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 15px;cursor: pointer;border-radius: 15px;box-shadow: 0 9px #999;}\n";
  ptr +=".button-on {background-color: #91F2A3;}\n";
  ptr +=".button-on:hover{background-color: #20910c;}\n";
  ptr +=".button-on:active {background-color: #20910c;box-shadow: 0 5px #666;transform: translateY(4px);}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  //ptr +="<h1>SiteGuardian Setup</h1>\n";
  ptr +="<img src = \n";
  ptr += SITE_GUARDIAN_LOGO;
  ptr +=">\n";
  ptr +="<h2>Welcome to the SiteGuardian Setup!</h2>\n";
  ptr +="<h3>This guide will assist you in configuring your device</h3>\n";
  ptr += "<a class=\"button button-on\" href=\"/io?PAGE=SELECT_MODE\">Begin Device Setup</a>\n";

  ptr +="<h3></h3>";
  ptr += "<p>Temperature: \n";
  ptr += Temperature;
  ptr+= " C</p>\n";
  ptr += "<p>Humidity: \n";
  ptr += Humidity;
  ptr += " %</p>\n";
  ptr += "<a class=\"button button-on\" href=\"/io?SENSORS=UPDATE\">Take New Readings</a>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}

String Page0_SelectMode_HTML(int OPERATING_MODE){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>Temperature & Humidity Sensor Demo</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 5px;} h1 {color: #444444;margin: 10px auto 20px;} h3 {color: #444444;margin-bottom: 15px;}\n";
  ptr +=".button {display: inline-block;padding: 15px 25px;background-color: #3498db;border: none;color: black;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 15px;cursor: pointer;border-radius: 15px;box-shadow: 0 9px #999;}\n";
  ptr +=".button-on {background-color: #91F2A3;}\n";
  ptr +=".button-on:hover{background-color: #20910c;}\n";
  ptr +=".button-on:active {background-color: #20910c;box-shadow: 0 5px #666;transform: translateY(4px);}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  //ptr +="<h1>SiteGuardian Setup</h1>\n";
  ptr +="<img src = \n";
  ptr += SITE_GUARDIAN_LOGO;
  ptr +=">\n";
  ptr +="<h2>Select an Operating Mode</h2>";
  ptr +="<h3>What would you like me to do with the measurements I collect?</h3>";
  ptr += "<p>Alert: Email me when something needs my attention</p>\n";
  ptr += "<p>Report: Record measurements and Email me a report regularly</p>\n";
  ptr += "<p>Sentry: Send to the SiteGuardian Data Service for advanced monitoring capabilities</p>\n";
  ptr += "<a class=\"button button-on\" href=\"/io?OPERATING_MODE=ALERT\">Use 'Alert' Mode</a>\n";
  ptr += "<a class=\"button button-on\" href=\"/io?OPERATING_MODE=REPORT\">Use 'Report' Mode</a>\n";
  ptr += "<a class=\"button button-on\" href=\"/io?OPERATING_MODE=SENTRY\">Use 'Sentry' Mode</a>\n";
  
  switch (OPERATING_MODE){
    case 2:
      ptr += "<p>Report Mode unavailable in this demo.</p>\n";
      break;
    case 3:
      ptr += "<p>Sentry Mode available in another demo.</p>\n";
      break;
    break;    
  }
  return ptr;
}

String Page1_DeviceName_HTML(String TextBox_Value){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>Temperature & Humidity Sensor Demo</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 5px;} h1 {color: #444444;margin: 10px auto 20px;} h3 {color: #444444;margin-bottom: 15px;}\n";
  ptr +=".button {display: inline-block;padding: 15px 25px;background-color: #3498db;border: none;color: black;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 15px;cursor: pointer;border-radius: 15px;box-shadow: 0 9px #999;}\n";
  ptr +=".button-on {background-color: #91F2A3;}\n";
  ptr +=".button-on:hover{background-color: #20910c;}\n";
  ptr +=".button-on:active {background-color: #20910c;box-shadow: 0 5px #666;transform: translateY(4px);}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  //ptr +="<h1>SiteGuardian Setup</h1>\n";
  ptr +="<img src = \n";
  ptr += SITE_GUARDIAN_LOGO;
  ptr +=">\n";
  ptr +="<h2>Step 1 of 6</h2>";
  ptr +="<h3>Let's start by giving me a name</h3>";
  //The textbox and Submit Button
  ptr +="<form action=\"/Page1_TextboxHandler\">Name: <input type=\"text\"  name=\"input1\">";
  ptr +="<input type=\"Submit\" value\"Submit\">";

  //Whatever was submitted through the textbox will be shown
  ptr +="<h1></h1>";
  ptr += "<h3>My Device Name: \n";
  ptr += TextBox_Value;
  ptr+= "</h3>\n";
  ptr += "<a class=\"button button-on\" href=\"/io?PAGE=STEP_2\">Next Step</a>\n";
  return ptr;
}

String Page2_Monitoring_Type_HTML(void){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>Temperature & Humidity Sensor Demo</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 5px;} h1 {color: #444444;margin: 10px auto 20px;} h3 {color: #444444;margin-bottom: 15px;}\n";
  ptr +=".button {display: inline-block;padding: 15px 25px;background-color: #3498db;border: none;color: black;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 15px;cursor: pointer;border-radius: 15px;box-shadow: 0 9px #999;}\n";
  ptr +=".button-on {background-color: #91F2A3;}\n";
  ptr +=".button-on:hover{background-color: #20910c;}\n";
  ptr +=".button-on:active {background-color: #20910c;box-shadow: 0 5px #666;transform: translateY(4px);}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  //ptr +="<h1>SiteGuardian Setup</h1>\n";
  ptr +="<img src = \n";
  ptr += SITE_GUARDIAN_LOGO;
  ptr +=">\n";

  ptr +="<h2>Step 2 of 6</h2>";
  ptr +="<h3>Please tell me which measurements should trigger an alert</h3>";

  ptr += "<a class=\"button button-on\" href=\"/io?ALERT_MODE=TEMPERATURE\">Temperature Only</a>\n";
  ptr += "<a class=\"button button-on\" href=\"/io?ALERT_MODE=HUMIDITY\">Humidity Only</a>\n";
  ptr += "<a class=\"button button-on\" href=\"/io?ALERT_MODE=BOTH\">Both</a>\n";
  return ptr;
}


String Page2A_Temperature_Mode_HTML(int Temperature_Type){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>Temperature & Humidity Sensor Demo</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 5px;} h1 {color: #444444;margin: 10px auto 20px;} h3 {color: #444444;margin-bottom: 15px;}\n";
  ptr +=".button {display: inline-block;padding: 15px 25px;background-color: #3498db;border: none;color: black;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 15px;cursor: pointer;border-radius: 15px;box-shadow: 0 9px #999;}\n";
  ptr +=".button-on {background-color: #91F2A3;}\n";
  ptr +=".button-on:hover{background-color: #20910c;}\n";
  ptr +=".button-on:active {background-color: #20910c;box-shadow: 0 5px #666;transform: translateY(4px);}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  //ptr +="<h1>SiteGuardian Setup</h1>\n";
  ptr +="<img src = \n";
  ptr += SITE_GUARDIAN_LOGO;
  ptr +=">\n";

  ptr +="<h2>Step 2 of 6</h2>";
  ptr +="<h3>What would you like me to watch for?</h3>";
  switch (Temperature_Type){
    case 1: ptr+= "<p>I'll let you know if it's too hot.</p>\n";
            break;
    case 2: ptr+= "<p>I'll let you know if it's too cold.</p>\n";
            break;
    case 3: ptr+= "<p>I'll let you know if it's outside of a range.</p>\n";
            break;
    break;
  }
  ptr += "<a class=\"button button-on\" href=\"/io?TEMPERATURE_MODE=HIGH\">Too Hot</a>\n";
  ptr += "<a class=\"button button-on\" href=\"/io?TEMPERATURE_MODE=LOW\">Too Cold</a>\n";
  ptr += "<a class=\"button button-on\" href=\"/io?TEMPERATURE_MODE=BOTH\">Outside Range</a>\n";
  
  //ptr +="<h3></h3>";
  //ptr += "<a class=\"button button-on\" href=\"/io?PAGE=STEP_3\">Next Step</a>\n";
  return ptr;
}

String Page2B_Humidity_Mode_HTML(int Humidity_Type){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>Temperature & Humidity Sensor Demo</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 5px;} h1 {color: #444444;margin: 10px auto 20px;} h3 {color: #444444;margin-bottom: 10px;}\n";
  ptr +=".button {display: inline-block;padding: 15px 25px;background-color: #3498db;border: none;color: black;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 15px;cursor: pointer;border-radius: 15px;box-shadow: 0 9px #999;}\n";
  ptr +=".button-on {background-color: #91F2A3;}\n";
  ptr +=".button-on:hover{background-color: #20910c;}\n";
  ptr +=".button-on:active {background-color: #20910c;box-shadow: 0 5px #666;transform: translateY(4px);}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  //ptr +="<h1>SiteGuardian Setup</h1>\n";
  ptr +="<img src = \n";
  ptr += SITE_GUARDIAN_LOGO;
  ptr +=">\n";

  ptr +="<h2>Step 2 of 6</h2>";
  ptr +="<h3>What would you like me to watch for?</h3>";
  switch (Humidity_Type){
    case 1: ptr+= "<p>I'll let you know if it's too humid.</p>\n";
            break;
    case 2: ptr+= "<p>I'll let you know if it's too dry.</p>\n";
            break;
    case 3: ptr+= "<p>I'll let you know if it's outside of a range.</p>\n";
            break;
    break;
  }
  ptr += "<a class=\"button button-on\" href=\"/io?HUMIDITY_MODE=HIGH\">Too Humid</a>\n";
  ptr += "<a class=\"button button-on\" href=\"/io?HUMIDITY_MODE=LOW\">Too Dry</a>\n";
  ptr += "<a class=\"button button-on\" href=\"/io?HUMIDITY_MODE=BOTH\">Outside Range</a>\n";
  ptr +="<h3></h3>";
  ptr += "<a class=\"button button-on\" href=\"/io?PAGE=STEP_3\">Next Step</a>\n";
  return ptr;
}

String Page2C_Combined_Mode_HTML(int Temperature_Type, int Humidity_Type){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>Temperature & Humidity Sensor Demo</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 5px;} h1 {color: #444444;margin: 10px auto 20px;} h3 {color: #444444;margin-bottom: 10px;}\n";
  ptr +=".button {display: inline-block;padding: 15px 25px;background-color: #3498db;border: none;color: black;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 15px;cursor: pointer;border-radius: 15px;box-shadow: 0 9px #999;}\n";
  ptr +=".button-on {background-color: #91F2A3;}\n";
  ptr +=".button-on:hover{background-color: #20910c;}\n";
  ptr +=".button-on:active {background-color: #20910c;box-shadow: 0 5px #666;transform: translateY(4px);}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  //ptr +="<h1>SiteGuardian Setup</h1>\n";
  ptr +="<img src = \n";
  ptr += SITE_GUARDIAN_LOGO;
  ptr +=">\n";

  ptr +="<h2>Step 2 of 6</h2>";
  ptr +="<h3>Select which Temperature and Humidity readings to watch for.</h3>";
  ptr +="<h3>Humidity Mode</h3>";
  switch (Humidity_Type){
    case 1: ptr+= "<p>I'll let you know if it's too humid.</p>\n";
            break;
    case 2: ptr+= "<p>I'll let you know if it's too dry.</p>\n";
            break;
    case 3: ptr+= "<p>I'll let you know if it's outside of a humidity range.</p>\n";
            break;
    break;
  }
  ptr += "<a class=\"button button-on\" href=\"/io?COMBINED_MODE=HIGH_HUMIDITY\">Too Humid</a>\n";
  ptr += "<a class=\"button button-on\" href=\"/io?COMBINED_MODE=LOW_HUMIDITY\">Too Dry</a>\n";
  ptr += "<a class=\"button button-on\" href=\"/io?COMBINED_MODE=BOTH_HUMIDIY\">Outside Range</a>\n";
  ptr +="<h3></h3>";
  ptr +="<h3>Temperature Mode</h3>";
  switch (Temperature_Type){
    case 1: ptr+= "<p>I'll let you know if it's too hot.</p>\n";
            break;
    case 2: ptr+= "<p>I'll let you know if it's too cold.</p>\n";
            break;
    case 3: ptr+= "<p>I'll let you know if it's outside of a temperature range.</p>\n";
            break;
    break;
  }
  ptr += "<a class=\"button button-on\" href=\"/io?COMBINED_MODE=HIGH_TEMPERATURE\">Too Hot</a>\n";
  ptr += "<a class=\"button button-on\" href=\"/io?COMBINED_MODE=LOW_TEMPERATURE\">Too Cold</a>\n";
  ptr += "<a class=\"button button-on\" href=\"/io?COMBINED_MODE=BOTH_TEMPERATURE\">Outside Range</a>\n";
  ptr +="<h3></h3>";
  ptr += "<a class=\"button button-on\" href=\"/io?PAGE=STEP_3\">Next Step</a>\n";
  return ptr;
}

String Page2D_Temperature_Thresholds_HTML(int Temperature_Type, float High_Temperature_Threshold, float Low_Temperature_Threshold){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>Temperature & Humidity Sensor Demo</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 5px;} h1 {color: #444444;margin: 10px auto 20px;} h3 {color: #444444;margin-bottom: 15px;}\n";
  ptr +=".button {display: inline-block;padding: 15px 25px;background-color: #3498db;border: none;color: black;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 15px;cursor: pointer;border-radius: 15px;box-shadow: 0 9px #999;}\n";
  ptr +=".button-on {background-color: #91F2A3;}\n";
  ptr +=".button-on:hover{background-color: #20910c;}\n";
  ptr +=".button-on:active {background-color: #20910c;box-shadow: 0 5px #666;transform: translateY(4px);}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  //ptr +="<h1>SiteGuardian Setup</h1>\n";
  ptr +="<img src = \n";
  ptr += SITE_GUARDIAN_LOGO;
  ptr +=">\n";
  ptr +="<h2>Step 2 of 6</h2>";
  switch (Temperature_Type){
    case 1:   ptr +="<form action=\"/Page2D_High_Temperature_TextboxHandler\"><input type=\"text\"  name=\"input1\">";
              ptr +="<input type=\"Submit\" value\"Submit\">";
              ptr += "<h3>Max Temperature: \n";
              ptr += High_Temperature_Threshold;
              ptr+= " Celcius</h3>\n";
              break;
    case 2:   ptr +="<form action=\"/Page2D_Low_Temperature_TextboxHandler\"><input type=\"text\"  name=\"input2\">";
              ptr +="<input type=\"Submit\" value\"Submit\">";
              ptr += "<h3>Min Temperature: \n";
              ptr += Low_Temperature_Threshold;
              ptr+= " Celcius</h3>\n";
              break;
    case 3:   ptr +="<form action=\"/Page2D_High_Temperature_TextboxHandler\"><input type=\"text\"  name=\"input1\">";
              //ptr +="<input type=\"Submit\" value\"Submit\">";
              ptr += "<h3>Max Temperature: \n";
              ptr += High_Temperature_Threshold;
              ptr+= " Celcius</h3>\n";

              ptr +="<form action=\"/Page2D_Low_Temperature_TextboxHandler\"><input type=\"text\"  name=\"input2\">";
              ptr +="<input type=\"Submit\" value\"Submit\">";
              ptr += "<h3>Min Temperature: \n";
              ptr += Low_Temperature_Threshold;
              ptr+= " Celcius</h3>\n";
              break;
    break;
  }
  ptr +="<h1></h1>";
  ptr += "<a class=\"button button-on\" href=\"/io?PAGE=STEP_3\">Next Step</a>\n";
  return ptr;
}

String Page3_Sleep_Time_HTML(String Timer_Value){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>Temperature & Humidity Sensor Demo</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 5px;} h1 {color: #444444;margin: 10px auto 20px;} h3 {color: #444444;margin-bottom: 15px;}\n";
  ptr +=".button {display: inline-block;padding: 15px 25px;background-color: #3498db;border: none;color: black;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 15px;cursor: pointer;border-radius: 15px;box-shadow: 0 9px #999;}\n";
  ptr +=".button-on {background-color: #91F2A3;}\n";
  ptr +=".button-on:hover{background-color: #20910c;}\n";
  ptr +=".button-on:active {background-color: #20910c;box-shadow: 0 5px #666;transform: translateY(4px);}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  //ptr +="<h1>SiteGuardian Setup</h1>\n";
  ptr +="<img src = \n";
  ptr += SITE_GUARDIAN_LOGO;
  ptr +=">\n";
  ptr +="<h2>Step 3 of 6</h2>";
  ptr +="<h3>Tell me how long to sleep between measurements (in minutes).</h3>";
  //The textbox and Submit Button
  ptr +="<form action=\"/Page3_TextboxHandler\"><input type=\"text\"  name=\"input1\">";
  ptr +="<input type=\"Submit\" value\"Submit\">";

  //Whatever was submitted through the textbox will be shown
  ptr +="<h1></h1>";
  ptr += "<h3>Current Timer: \n";
  ptr += Timer_Value;
  ptr+= " minutes</h3>\n";
  ptr += "<a class=\"button button-on\" href=\"/io?PAGE=STEP_4\">Next Step</a>\n";
  return ptr;
}

String Page4_Contact_HTML(String Contact_Link){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>Temperature & Humidity Sensor Demo</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 5px;} h1 {color: #444444;margin: 10px auto 20px;} h3 {color: #444444;margin-bottom: 15px;}\n";
  ptr +=".button {display: inline-block;padding: 15px 25px;background-color: #3498db;border: none;color: black;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 15px;cursor: pointer;border-radius: 15px;box-shadow: 0 9px #999;}\n";
  ptr +=".button-on {background-color: #91F2A3;}\n";
  ptr +=".button-on:hover{background-color: #20910c;}\n";
  ptr +=".button-on:active {background-color: #20910c;box-shadow: 0 5px #666;transform: translateY(4px);}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  //ptr +="<h1>SiteGuardian Setup</h1>\n";
  ptr +="<img src = \n";
  ptr += SITE_GUARDIAN_LOGO;
  ptr +=">\n";
  ptr +="<h2>Step 4 of 6</h2>";
  ptr +="<h3>Tell me where you'd like data sent.  I can send alerts to your email or text you.</h3>";
  ptr +="<p>Email: xxxxxxxxx@gmail.com</p>";
  ptr +="<p>Text: xxxxxxxxxx@msg.telus.com</p>";
  //The textbox and Submit Button
  ptr +="<form action=\"/Page4_TextboxHandler\"><input type=\"text\"  name=\"input1\">";
  ptr +="<input type=\"Submit\" value\"Submit\">";

  //Whatever was submitted through the textbox will be shown
  ptr +="<h1></h1>";
  ptr += "<h3>Destination: \n";
  ptr += Contact_Link;
  ptr+= "</h3>\n";
  ptr += "<a class=\"button button-on\" href=\"/io?PAGE=STEP_5\">Next Step</a>\n";
  return ptr;
}

String Page5_Review_HTML(String Device_Name, String High_Temp_Threshold, int Sleep_Time, String Contact_Link){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>Temperature & Humidity Sensor Demo</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 5px;} h1 {color: #444444;margin: 10px auto 20px;} h3 {color: #444444;margin-bottom: 10px;}\n";
  ptr +=".button {display: inline-block;padding: 15px 25px;background-color: #3498db;border: none;color: black;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 15px;cursor: pointer;border-radius: 15px;box-shadow: 0 9px #999;}\n";
  ptr +=".button-on {background-color: #91F2A3;}\n";
  ptr +=".button-on:hover{background-color: #20910c;}\n";
  ptr +=".button-on:active {background-color: #20910c;box-shadow: 0 5px #666;transform: translateY(4px);}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  //ptr +="<h1>SiteGuardian Setup</h1>\n";
  ptr +="<img src = \n";
  ptr += SITE_GUARDIAN_LOGO;
  ptr +=">\n";
  ptr +="<h2>Step 5 of 6</h2>";
  ptr +="<h3>Let's review my settings to make sure everything looks okay</h3>";
  
  ptr += "<h3>1. My name is \n";
  ptr += Device_Name;
  ptr+= "</h3>\n";

  ptr += "<h3>2. I'll send alerts to \n";
  ptr += Contact_Link;
  ptr+= "</h3>\n";

  ptr += "<h3>3. I'll let you know if the temperature exceeds \n";
  ptr += High_Temp_Threshold;
  ptr+= " C</h3>\n";

  ptr += "<h3>4. I'll sleep for \n";
  ptr += Sleep_Time;
  ptr+= " minutes before checking the temperature again</h3>\n";

  ptr +="<p>If everything looks okay, continue to WiFi Configuration</p>";
  ptr +="<a class=\"button button-on\" href=\"_ac/config\">Wifi Configuration</a>\n";
  return ptr;
}

String Page6_Complete_HTML(String WiFi_Name){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>Temperature & Humidity Sensor Demo</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 5px;} h1 {color: #444444;margin: 10px auto 20px;} h3 {color: #444444;margin-bottom: 10px;}\n";
  ptr +=".button {display: inline-block;padding: 15px 25px;background-color: #3498db;border: none;color: black;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 15px;cursor: pointer;border-radius: 15px;box-shadow: 0 9px #999;}\n";
  ptr +=".button-on {background-color: #91F2A3;}\n";
  //ptr +=".button {display: inline-block;padding: 15px 25px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 15px;cursor: pointer;border-radius: 15px;box-shadow: 0 9px #999;}\n";
  //ptr +=".button-on {background-color: #133b54;}\n";
  ptr +=".button-on:hover{background-color: #20910c;}\n";
  ptr +=".button-on:active {background-color: #20910c;box-shadow: 0 5px #666;transform: translateY(4px);}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  //ptr +="<h1>SiteGuardian Setup</h1>\n";
  ptr +="<img src = \n";
  ptr += SITE_GUARDIAN_LOGO;
  ptr +=">\n";
  ptr +="<h2>Step 6 of 6</h2>";
  ptr += "<h3>I can now connect to \n";
  ptr += WiFi_Name;
  ptr+= " when I need to alert you.</h3>\n";
  ptr +="<h3>Thank you for choosing SiteGuardian and enjoy your new device!</h3>";
  ptr +="<p>You can enter configuration mode again to change any settings by pressing the 'RESET' button on the side of the device 3 times</p>";

  ptr +="<p>I'll send you a test notification when you finish setup.</p>";
  ptr += "<a class=\"button button-on\" href=\"/io?SETUP=COMPLETE\">Finish Setup</a>\n";
  return ptr;
}