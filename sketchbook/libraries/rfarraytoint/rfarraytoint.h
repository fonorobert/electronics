#include "Arduino.h"

int rfArrToInt(uint8_t * msg, int msglength) {
  char valueArray[msglength + 1];
  for(int i = 0; i < msglength; i++){
    valueArray[i] = (char)msg[i];
  }
  valueArray[msglength] = '\0';
  int value = atoi(valueArray);
  return value;
}
