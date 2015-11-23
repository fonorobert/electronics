#include "Arduino.h"

int tempMeter(int tempPin, float aref_voltage) {
  int tempReading = analogRead(tempPin);

  float voltage = tempReading;
  voltage = voltage * (aref_voltage / 1023.0);

  float temperatureK = voltage * 100 ;
  float temperatureC = temperatureK - 273.15;
  return floor(temperatureC);
}
