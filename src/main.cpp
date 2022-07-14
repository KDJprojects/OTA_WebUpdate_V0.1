/*#include <Arduino.h>

void setup() {
Serial.begin(115200);
}

void loop() {
Serial.println("Sucesfully Updated to V0.1");
delay(3000);
}
*/

#include <Arduino.h>
#include "AutoConnect.h"
#include "HTML_Builder.h"
#include <WiFi.h>
#include "EEPROM_Library.h"
#include "Battery_Measurement.h"
#include "GPIO_Pinouts.h"
#include "Board_ID_Measurement.h"
#include "Sleep_Library.h"
#include "LED_Control_Library.h"
#include "SHT30_Measurement.h"
#include "ESP_Mail_Client.h"
#include "MAC_Handler.h"

#define HIGH_BRIGHTNESS 255
#define HALF_BRIGHTNESS 128
#define LOW_BRIGHTNESS  10
#define Config_Timeout_mS 600000  //ten minute timeout when in CONFIG mode

#define SMTP_server "smtp.gmail.com"
#define SMTP_Port 465
#define sender_email "siteguardiantest@gmail.com"
#define sender_password "dmzjobzcqorphvpe"
bool SENT_SUCESSFULLY = 1;
//SHT3x Sensor;
const char* PARAM_INPUT_1 = "input1";
const char* PARAM_INPUT_2 = "input2";
int OPERATING_MODE = 0;
int ALERT_MODE = 0;
int TEMPERATURE_ALERT_TYPE = 0;
int HUMIDITY_ALERT_TYPE = 0;
int COMBINED_MODE_TYPE = 0;
float High_Temp_Threshold = 25.0;
float Low_Temp_Threshold;
float High_Humidity_Threshold;
float Low_Humidity_Threshold;
bool Already_Sent = 0;
bool Never_Sent;
bool ALERT_TRIGGERED;
int SENT_EMAILS;
String TextBox;
String Sleep_Textbox = "5";
String Device_Name;
String Contact_Link;
String MAC_Address;
int Sleep_Time_S = 600;
float Temperature;
float Humidity;
String TOKEN;
float Battery_Voltage;
float BoardID_1_Voltage;
float BoardID_2_Voltage;
int RESET_COUNT;
bool CONFIG_MODE;
bool PAIRED;
bool PAIRED_FLASH_INDICATOR;
int Start_Time;
bool Battery_LOW;
bool CONNECTED_TO_AP;
bool CONNECTED_TO_AP_FLASH_INDICATOR;

WebServer SERVER;
AutoConnect Portal(SERVER);
AutoConnectConfig config;
HTTPClient http;
WiFiClient client;
String WiFi_Strength;
SMTPSession smtp;

void Measure_Sensors(void){
  Battery_Voltage = Measure_Battery();
  Activate_AUX_Power();
    BoardID_1_Voltage = Board_ID_Measurement(1);
    BoardID_2_Voltage = Board_ID_Measurement(2);
    Measure_Temp_and_Humidity(Temperature, Humidity);
    if (Temperature >= High_Temp_Threshold){
      ALERT_TRIGGERED = true;
    }
  Deactivate_AUX_Power();
}

void RootPage(void){
  String RootPage_HTML = Build_HTML(String (Temperature, 2), String(Humidity, 2));      //Build a new HTML string
  SERVER.send(200, "text/html", RootPage_HTML);       //Draw and display the web page
  CONNECTED_TO_AP = true;
  if (CONNECTED_TO_AP == true && CONNECTED_TO_AP_FLASH_INDICATOR == false){
    for (int i=0; i<3; i++){
      Blink_Color(HIGH_BRIGHTNESS, 0, HIGH_BRIGHTNESS, 150);
      delay(150);
    }
    CONNECTED_TO_AP_FLASH_INDICATOR = true;
    Set_Color(LOW_BRIGHTNESS, 0, LOW_BRIGHTNESS);
  }
}

void Page0_MODE(void){
  String HTML = Page0_SelectMode_HTML(OPERATING_MODE);
  SERVER.send(200, "text/html", HTML);
}
void Page1_NAME(void){
  String HTML = Page1_DeviceName_HTML(Device_Name);
  SERVER.send(200, "text/html", HTML);
}


void Page2_ALERT_TYPE(void){
  String HTML = Page2_Monitoring_Type_HTML();
  SERVER.send(200, "text/html", HTML);
}
void Page2A_TEMPERATURE_TYPE(void){
  String HTML = Page2A_Temperature_Mode_HTML(TEMPERATURE_ALERT_TYPE);
  SERVER.send(200, "text/html", HTML);
}
void Page2B_HUMIDITY_TYPE(void){
  String HTML = Page2B_Humidity_Mode_HTML(HUMIDITY_ALERT_TYPE);
  SERVER.send(200, "text/html", HTML);
}
void Page2C_COMBINED_TYPE(void){
  String HTML = Page2C_Combined_Mode_HTML(TEMPERATURE_ALERT_TYPE, HUMIDITY_ALERT_TYPE);
  SERVER.send(200, "text/html", HTML);
}
void Page2D_TEMPERATURE_THRESHOLDS(void){
  String HTML = Page2D_Temperature_Thresholds_HTML(TEMPERATURE_ALERT_TYPE, High_Temp_Threshold, Low_Temp_Threshold);
  SERVER.send(200, "text/html", HTML);
}

void Page3_SLEEP_TIME(void){
  String HTML = Page3_Sleep_Time_HTML(Sleep_Textbox);
  SERVER.send(200, "text/html", HTML);
}

void Page4_CONTACT(void){
  String HTML = Page4_Contact_HTML(Contact_Link);
  SERVER.send(200, "text/html", HTML);
}

void Page5_REVIEW(void){
  int Minutes_to_Sleep = Sleep_Time_S / 60;
  String HTML = Page5_Review_HTML(Device_Name, String(High_Temp_Threshold, 1), Minutes_to_Sleep, Contact_Link);
  SERVER.send(200, "text/html", HTML);
}

void Page6_COMPLETE(void){
  Serial.println("Name: " + Device_Name);
  Serial.println("High Temp Threshold: " + String(High_Temp_Threshold, 2));
  String HTML = Page6_Complete_HTML(WiFi.SSID());
  SERVER.send(200, "text/html", HTML);
}


void sendRedirect(String uri){
  SERVER.sendHeader("Location", uri, true);
  SERVER.send(302, "text/plain", "");
  SERVER.client().stop();
}

void handleGPIO(void){
  Start_Time = millis();
  if (SERVER.arg("SENSORS") == "UPDATE"){
    Set_Color(HIGH_BRIGHTNESS, 0, HIGH_BRIGHTNESS);
    Measure_Sensors();
    Set_Color(LOW_BRIGHTNESS, 0, LOW_BRIGHTNESS);
    sendRedirect("/");
  }

  if (SERVER.arg("PAGE") == "SELECT_MODE"){
    sendRedirect("/Page0_SelectMode");
  }

  if (SERVER.arg("OPERATING_MODE") == "ALERT"){
    OPERATING_MODE = 1;
    sendRedirect("/Page1_Name");
  }
  if (SERVER.arg("OPERATING_MODE") == "REPORT"){
    OPERATING_MODE = 2;
    sendRedirect("/Page0_SelectMode");
  }
  if (SERVER.arg("OPERATING_MODE") == "SENTRY"){
    OPERATING_MODE = 3;
    sendRedirect("/Page0_SelectMode");
  }

  if (SERVER.arg("PAGE") == "STEP_2"){
    sendRedirect("/Page2_AlertType");
  }

  //Temperature Mode Page
  if (SERVER.arg("ALERT_MODE") == "TEMPERATURE"){ 
    TEMPERATURE_ALERT_TYPE = 0;
    sendRedirect("/Page2A_TemperatureType");
  }
  if (SERVER.arg("TEMPERATURE_MODE") == "HIGH"){ 
    TEMPERATURE_ALERT_TYPE = 1;
    sendRedirect("/Page2D_Temperature_Thresholds");
    //sendRedirect("/Page2A_TemperatureType");
  }
  if (SERVER.arg("TEMPERATURE_MODE") == "LOW"){ 
    TEMPERATURE_ALERT_TYPE = 2;
    sendRedirect("/Page2D_Temperature_Thresholds");
  }
  if (SERVER.arg("TEMPERATURE_MODE") == "BOTH"){ 
    TEMPERATURE_ALERT_TYPE = 3;
    sendRedirect("/Page2D_Temperature_Thresholds");
  }

  //Humidity Mode Page
  if (SERVER.arg("ALERT_MODE") == "HUMIDITY"){ 
    HUMIDITY_ALERT_TYPE = 0;
    sendRedirect("/Page2B_HunidityType");
  }
  if (SERVER.arg("HUMIDITY_MODE") == "HIGH"){ 
    HUMIDITY_ALERT_TYPE = 1;
    sendRedirect("/Page2B_HunidityType");
  }
  if (SERVER.arg("HUMIDITY_MODE") == "LOW"){ 
    HUMIDITY_ALERT_TYPE = 2;
    sendRedirect("/Page2B_HunidityType");
  }
  if (SERVER.arg("HUMIDITY_MODE") == "BOTH"){ 
    HUMIDITY_ALERT_TYPE = 3;
    sendRedirect("/Page2B_HunidityType");
  }

  //Combined Mode Page
  if (SERVER.arg("ALERT_MODE") == "BOTH"){ 
    sendRedirect("/Page2C_CombinedType");
  }
  if (SERVER.arg("COMBINED_MODE") == "HIGH_HUMIDITY"){ 
    HUMIDITY_ALERT_TYPE = 1;
    sendRedirect("/Page2C_CombinedType");
  }
  if (SERVER.arg("COMBINED_MODE") == "LOW_HUMIDITY"){ 
    HUMIDITY_ALERT_TYPE = 2;
    sendRedirect("/Page2C_CombinedType");
  }
  if (SERVER.arg("COMBINED_MODE") == "BOTH_HUMIDITY"){ 
    HUMIDITY_ALERT_TYPE = 3;
    sendRedirect("/Page2C_CombinedType");
  }
  if (SERVER.arg("COMBINED_MODE") == "HIGH_TEMPERATURE"){ 
    TEMPERATURE_ALERT_TYPE = 1;
    sendRedirect("/Page2C_CombinedType");
  }
  if (SERVER.arg("COMBINED_MODE") == "LOW_TEMPERATURE"){ 
    TEMPERATURE_ALERT_TYPE = 2;
    sendRedirect("/Page2C_CombinedType");
  }
  if (SERVER.arg("COMBINED_MODE") == "BOTH_TEMPERATURE"){ 
    TEMPERATURE_ALERT_TYPE = 3;
    sendRedirect("/Page2C_CombinedType");
  }
  //Button to redirect to Step 3
  if (SERVER.arg("PAGE") == "STEP_3"){
    sendRedirect("/Page3_Sleep_Timer");
  }


  //Button to redirect to step 4
  if (SERVER.arg("PAGE") == "STEP_4"){
    sendRedirect("/Page4_Contact");
  }
  //Button to redirect to step 4
  if (SERVER.arg("PAGE") == "STEP_5"){
    sendRedirect("/Page5_Review");
  }
  if (SERVER.arg("SETUP") == "COMPLETE"){
    Save_Configuration(Device_Name, High_Temp_Threshold, Sleep_Time_S, Contact_Link); 
    Save_Reset_Count(0);  
    esp_restart();
  }

}  

void Page1_TextBoxHandler(void){
  TextBox = SERVER.arg(PARAM_INPUT_1);
  Device_Name = TextBox;
  Serial.print("Value Passed: ");
  Serial.println(TextBox);
  sendRedirect("/Page1_Name");
}

void Page2D_High_Temperature_TextBoxHandler(void){
  Serial.println("Submit Triggered");
  String Box1 = SERVER.arg(PARAM_INPUT_1);
  String Box2 = SERVER.arg(PARAM_INPUT_2);
  High_Temp_Threshold = Box1.toFloat();
  Low_Temp_Threshold = Box2.toFloat();
  Serial.print("Box 1 Passed: ");
  Serial.println(High_Temp_Threshold);
  Serial.print("Box 2 Passed: ");
  Serial.println(Low_Temp_Threshold);
  sendRedirect("/Page2D_Temperature_Thresholds");
}
void Page2D_Low_Temperature_TextBoxHandler(void){
  Serial.println("Low Temp Submit Triggered");
  TextBox = SERVER.arg(PARAM_INPUT_2);
  Low_Temp_Threshold = TextBox.toFloat();
  Serial.print("Value Passed: ");
  Serial.println(Low_Temp_Threshold);
  sendRedirect("/Page2D_Temperature_Thresholds");
}

void Page3_TextBoxHandler(void){
  Sleep_Textbox = SERVER.arg(PARAM_INPUT_1);
  int minutes = Sleep_Textbox.toInt();
  if (minutes < 1){
    Sleep_Textbox = "I can't sleep for less than 1 minute";
  }
  if (minutes > 1441){
    Sleep_Textbox = "I can't stay asleep longer than 1 day";
  }
  Sleep_Time_S = minutes * 60;
  Serial.print("Value Passed: ");
  Serial.println(Sleep_Textbox);
  sendRedirect("/Page3_Sleep_Timer");
}
void Page4_TextBoxHandler(void){
  Contact_Link = SERVER.arg(PARAM_INPUT_1);
  Serial.print("Value Passed: ");
  Serial.println(TextBox);
  sendRedirect("/Page4_Contact");
}

bool Check_For_WiFi_Credentials(void){
  AutoConnectCredential credential;
  uint8_t ent = credential.entries();
  if (ent){
    Serial.printf("Available %d entries.\n", ent);
    return true;
  }
  else {
    Serial.println("No credentials saved.");
    return false;
  }
}

void deleteAllCredentials(void) {
  AutoConnectCredential credential;
  station_config_t config;
  uint8_t ent = credential.entries();

  Serial.println("AutoConnectCredential deleting");
  if (ent)
    Serial.printf("Available %d entries.\n", ent);
  else {
    Serial.println("No credentials saved.");
    return;
  }

  while (ent--) {
    credential.load((int8_t)0, &config);
    if (credential.del((const char*)&config.ssid[0]))
      Serial.printf("%s deleted.\n", (const char*)config.ssid);
    else
      Serial.printf("%s failed to delete.\n", (const char*)config.ssid);
  }
}


void Start_Server(void){
  Serial.println("Server now starting...");
  //config.ota = AC_OTA_BUILTIN;
  Portal.append("/Page6_Complete", "Complete Setup");
  config.autoReconnect = true;
  config.autoRise = true;
  config.retainPortal = true;
  config.portalTimeout = 1;
  String HotSpotID = "SiteGuardian " + MAC_Address;
  Serial.println(HotSpotID);
  config.apid = HotSpotID;         //Set the name of the HotSpot (available when not connected to WiFi)
  config.title = "Temp & Humidity WiFi Setup";    //Set the name of the HotSpot's configuration Portal
  config.bootUri = AC_ONBOOTURI_HOME;   //When connecting to this hotspot, direct the user to the HOME url (customized)
  Portal.config(config);
  SERVER.on("/", RootPage);
  SERVER.on("/Page0_SelectMode", Page0_MODE);
  SERVER.on("/Page1_Name", Page1_NAME);
  SERVER.on("/Page2_AlertType", Page2_ALERT_TYPE);
  SERVER.on("/Page2A_TemperatureType", Page2A_TEMPERATURE_TYPE);
  SERVER.on("/Page2B_HunidityType", Page2B_HUMIDITY_TYPE);
  SERVER.on("/Page2C_CombinedType", Page2C_COMBINED_TYPE);
  SERVER.on("/Page2D_Temperature_Thresholds", Page2D_TEMPERATURE_THRESHOLDS);
  SERVER.on("/Page2C_CombinedType", Page2C_COMBINED_TYPE);
  SERVER.on("/Page2C_CombinedType", Page2C_COMBINED_TYPE);
  SERVER.on("/Page3_Sleep_Timer", Page3_SLEEP_TIME);
  SERVER.on("/Page4_Contact", Page4_CONTACT);
  SERVER.on("/Page5_Review", Page5_REVIEW);
  SERVER.on("/Page6_Complete", Page6_COMPLETE);
  SERVER.on("/io", handleGPIO);
  SERVER.on("/Page1_TextboxHandler", Page1_TextBoxHandler);
  SERVER.on("/Page2D_High_Temperature_TextboxHandler", Page2D_High_Temperature_TextBoxHandler);
  SERVER.on("/Page2D_Low_Temperature_TextboxHandler", Page2D_Low_Temperature_TextBoxHandler);
  SERVER.on("/Page3_TextboxHandler", Page3_TextBoxHandler);
  SERVER.on("/Page4_TextboxHandler", Page4_TextBoxHandler);
  if (Portal.begin() == true){
    Serial.print("Sucessfully connected to: " + WiFi.SSID());
    Serial.print(", Assigned IP: " + WiFi.localIP().toString());
    WiFi_Strength = String(WiFi.RSSI());
    Serial.print(", Strength: ");
    Serial.println(WiFi_Strength);
    if (CONFIG_MODE == false){
    for (int i=0; i<3; i++){
        Blink_Color(0, 0, LOW_BRIGHTNESS, 500);
        delay(250);
    }
    Set_Color(0, 0, LOW_BRIGHTNESS);
    }
  }
  else {
    if (CONFIG_MODE == false){
     Blink_Color(LOW_BRIGHTNESS, 0, 0, 250);
    }
  }
}

/*
int Submit_P0003_Data(void){
  int error = 0;
  WiFiClient client;
  HTTPClient http;
  const char* ServerName = "http://factorymonitoringdeviceservice-dev.us-east-1.elasticbeanstalk.com/api/v1/Data";
  http.begin(client, ServerName);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", TOKEN);
  String POST_String = "{\"airTemperature\": {\"value\":";
  POST_String += Temperature;      
  POST_String += ",\"isBellowRange\": false,\"isOverRange\": false}, \"airHumidity\": {\"value\":";
  POST_String += Humidity;
  POST_String += ",\"isBellowRange\": false,\"isOverRange\": false}, \"batterySupplyVoltage\": {\"value\":";
  POST_String += Battery_Voltage;
  POST_String += ",\"isBellowRange\": false,\"isOverRange\": false}";
  POST_String += "}";

  int httpResponseCode = http.POST(POST_String);
  String payload = "--";
  if (httpResponseCode == 200){
    Serial.println("Success!");
    payload = http.getString();
    //Serial.println(payload);
    for (int i=0; i<3; i++){
        Blink_Color(0, 0, LOW_BRIGHTNESS, 500);
        delay(250);
    }
  }
  if (httpResponseCode == 400){
    Serial.println("POST Request had incorrect formatting.");
    error = 1;
  }
  if (httpResponseCode == 401){
    Serial.println("Unauthorized Security Token.");
      for (int i=0; i<3; i++){
        Blink_Color(LOW_BRIGHTNESS, 0, LOW_BRIGHTNESS, 250);
        delay(250);
      }
      error = 2;
  }
  http.end();
  return error;
}
*/
void Send_Test_Email(void){
 smtp.debug(1);
  ESP_Mail_Session session;
  session.server.host_name = SMTP_server ;
  session.server.port = SMTP_Port;
  session.login.email = sender_email;
  session.login.password = sender_password;
  session.login.user_domain = "";

  SMTP_Message message;
  message.sender.name = "SiteGuardian";
  message.sender.email = sender_email;
  message.subject = Device_Name + " Email Test";
  message.addRecipient("Dover Animal Hospital", Contact_Link);

  String htmlMsg = "<div style=\"color:##FFBE33;\">\n";
         htmlMsg += "<h2>This is a test email to confirm that you can receive notifications.</h2><p>Thank you for choosing SiteGuardian</p></div>";
         
  message.html.content = htmlMsg.c_str();
  message.html.content = htmlMsg.c_str();
  message.text.charSet = "us-ascii";
  message.html.transfer_encoding = Content_Transfer_Encoding::enc_7bit;

  if (!smtp.connect(&session))
    return;
  if (!MailClient.sendMail(&smtp, &message)){
    Serial.println("Error sending Email, " + smtp.errorReason());
    for (int i=0; i<3; i++){
        Blink_Color(HIGH_BRIGHTNESS, 0, HIGH_BRIGHTNESS, 500);
        delay(250);
    }
  }  
}

void Send_Alert(void){
  smtp.debug(1);
  ESP_Mail_Session session;
  session.server.host_name = SMTP_server ;
  session.server.port = SMTP_Port;
  session.login.email = sender_email;
  session.login.password = sender_password;
  session.login.user_domain = "";

  SMTP_Message message;
  message.sender.name = "SiteGuardian";
  message.sender.email = sender_email;
  message.subject = Device_Name + " High Temperature Alert!";
  message.addRecipient("Dover Animal Hospital", Contact_Link);

  String htmlMsg = "<div style=\"color:##FFBE33;\">\n";
         htmlMsg += "<h2>The ";
         htmlMsg += Device_Name;
         htmlMsg += " air temperature is currently ";
         htmlMsg += String(Temperature, 2);
         htmlMsg +="C, you requested to be notified when it exceeds ";
         htmlMsg += String(High_Temp_Threshold, 2);
         htmlMsg += "C.</h2><p>Thank you for choosing SiteGuardian</p></div>";
         
  message.html.content = htmlMsg.c_str();
  message.html.content = htmlMsg.c_str();
  message.text.charSet = "us-ascii";
  message.html.transfer_encoding = Content_Transfer_Encoding::enc_7bit;

  if (!smtp.connect(&session))
    return;
  if (!MailClient.sendMail(&smtp, &message)){
    Serial.println("Error sending Email, " + smtp.errorReason());
    for (int i=0; i<3; i++){
        Blink_Color(HIGH_BRIGHTNESS, 0, HIGH_BRIGHTNESS, 500);
        delay(250);
    }
  }  
}

void setup() {
Serial.begin(115200);
Serial.println("Running NEW demo Firmware");
delay(1000);
Define_Pins();
Set_Color(0, LOW_BRIGHTNESS, 0);
MAC_Address = Get_MAC_Address();
if (Check_For_WiFi_Credentials() == false){
  CONFIG_MODE = true;
}
RESET_COUNT = Get_Reset_Count();
RESET_COUNT ++;
Serial.print("Reset Count: ");
Save_Reset_Count(RESET_COUNT);
Serial.println(RESET_COUNT);
if (RESET_COUNT > 2){
  CONFIG_MODE = true;
}
if (CONFIG_MODE == true){
  Set_Color(LOW_BRIGHTNESS, 0, 0);
  Save_Email_Status(0);
  Save_Test_Email_Status(false);
  Save_Configuration(MAC_Address, 25.0, 300, "");   
  //Save_Reset_Count(0);
  Start_Server();
  deleteAllCredentials();
  sendRedirect("/_ac/disc");
  WiFi.disconnect(false, true);
}
Load_Configuration(Device_Name, High_Temp_Threshold, Sleep_Time_S, Contact_Link);

Measure_Sensors();
delay(1000);
Save_Reset_Count(0);
if (Battery_Voltage < 3.3){
  Battery_LOW = true;
  Serial.println("Low Battery detected.");
  //Set_Color(LOW_BRIGHTNESS, 0, 0);
}

bool Test_Email_Sent = Load_Test_Email_Status();
if (CONFIG_MODE == false && Test_Email_Sent == false && ALERT_TRIGGERED == false){
  Serial.println("Sending a Test Email");
  Start_Server();
  Send_Test_Email();
  if (SENT_SUCESSFULLY == true){
    Save_Test_Email_Status(true);
  for (int i=0; i<3; i++){
        Blink_Color(0, 0, HIGH_BRIGHTNESS, 500);
        delay(250);
    }
  }
}

if (ALERT_TRIGGERED == true && CONFIG_MODE == false){
  Serial.println("ALERT TRIGGERED!");
  for (int i=0; i<3; i++){
        Blink_Color(0, 0, LOW_BRIGHTNESS, 500);
        delay(250);
    }
  Set_Color(0, 0, LOW_BRIGHTNESS);
  SENT_EMAILS = Load_Email_Status();
  if (SENT_EMAILS < 3){
  Start_Server();
  Send_Alert();
  
  if (SENT_SUCESSFULLY == true){
    SENT_EMAILS ++;
    Save_Email_Status(SENT_EMAILS);
    Save_Test_Email_Status(true);
  for (int i=0; i<3; i++){
        Blink_Color(0, 0, HIGH_BRIGHTNESS, 500);
        delay(250);
    }
  }
  }
  if (SENT_EMAILS >= 3){
    for (int i=0; i<3; i++){
        Blink_Color(0, HIGH_BRIGHTNESS, 0, 500);
        delay(250);
    }
  }
}
//Serial.print("Sending Data...");
/*
switch (Submit_P0003_Data()){
  case 0: Save_Reset_Count(0);
          break;
  case 1: Serial.println("Post had incorrect formatting.");
          break;
  case 2: Serial.println("Security Token expired.");
          Request_Token();    //get a new token
          if (Submit_P0003_Data() == 0){
            Save_Reset_Count(0);
          }
          break;
  break;
}
*/
if (CONFIG_MODE == false){
  if (Battery_LOW == true){
    Serial.println("Low Battery Sleep Mode");
    Low_Battery_Sleep(Sleep_Time_S);
  }
  if (Battery_LOW == false){
    Serial.println("Regular Sleep Mode");
    Start_Timer_Sleep(Sleep_Time_S);
  }
}
Set_Color(LOW_BRIGHTNESS, 0, LOW_BRIGHTNESS);
Serial.println("Config Mode active, the device will go back to deep sleep when reset or after ten minutes.");
Start_Time = millis();
}

void loop() {
Portal.handleClient();
Portal.handleRequest();
//If the user connects to a WiFi network, let them know by flashing yellow.
if (WiFi.isConnected() == true){
  PAIRED = true;
  if (PAIRED == true && PAIRED_FLASH_INDICATOR == false){
    
    for (int i=0; i<3; i++){
      Blink_Color(HIGH_BRIGHTNESS, 0, HIGH_BRIGHTNESS, 250);
      delay(250);
    }
    PAIRED_FLASH_INDICATOR = true;
    Set_Color(LOW_BRIGHTNESS, 0, LOW_BRIGHTNESS);
    
  }
}

if ((millis() - Start_Time) >= Config_Timeout_mS){
  Serial.println("Config has timed out, going to deep sleep until reset.");
  esp_deep_sleep_start();
}
}
