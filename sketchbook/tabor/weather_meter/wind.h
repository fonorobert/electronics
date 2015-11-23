#include "Arduino.h"

int windMeter(int windPin, float aref_voltage){
  int turn = 0;
  int min = 200;

  for (int t = millis(); millis() - t < 1000; t = t){
    int light = analogRead(A0); //read the value
    //Serial.println(light); //to use only in case of emergency 😛
    if (light < min){ //if there is light and the trigger is on, put turn+1 and turn off the trigger
      turn++;
    }
    delay(10);
  }
  float kph = ((2*3.14*0.000020)/1*10080)*turn;
  int result = floor(kph);
  return turn;
}
