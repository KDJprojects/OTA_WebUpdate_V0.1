#include <WiFi.h>
#include <Arduino.h>

String Get_MAC_Address(void){
  String MAC = WiFi.macAddress();
  MAC.remove(2,1);
  MAC.remove(4,1);
  MAC.remove(6,1);
  MAC.remove(8,1);
  MAC.remove(10,1);
  Serial.print("Edited MAC: ");
  Serial.println(MAC);
  return MAC;
}