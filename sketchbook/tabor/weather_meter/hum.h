#include "Arduino.h"

int humMeter(int humPin, float aref_voltage) {
  int humReading = analogRead(humPin);
  int result = map(humReading, 0, 1023, 20, 95);
  // int result = humReading/aref_voltage;
  return result;
}
