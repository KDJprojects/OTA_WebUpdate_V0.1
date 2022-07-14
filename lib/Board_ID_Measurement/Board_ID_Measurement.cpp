#include <Arduino.h>
#include "GPIO_Pinouts.h"

float Board_ID_Measurement(int ID){
    //Take twenty samples of the board ID circuit
    float Board_ID_Voltage = 0.0;
        for (int i = 0; i < 20; i++){
            switch (ID){
                case 1:
                    Board_ID_Voltage += analogRead(BoardID_1);
                    break;
                case 2:
                    Board_ID_Voltage += analogRead(BoardID_2);
                    break;
                break;
            }
            delay(1);
        }
    Board_ID_Voltage = Board_ID_Voltage / 20;
  Board_ID_Voltage = 2 * 3.3 * Board_ID_Voltage / 4096;
  Serial.print("ID");
  Serial.print(ID);
  Serial.print(" Voltage= ");
  Serial.println(Board_ID_Voltage, 3);    
}