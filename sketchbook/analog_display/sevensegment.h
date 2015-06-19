#include "Arduino.h"
int seven_seg_digits[10][7]{
  {1,0,1,1,1,1,1},
  {0,0,0,1,0,0,1},
  {0,1,1,1,1,1,0},
  {0,1,1,1,0,1,1},
  {1,1,0,1,0,0,1},
  {1,1,1,0,0,1,1},
  {1,1,1,0,1,1,1},
  {0,0,1,1,0,0,1},
  {1,1,1,1,1,1,1},
  {1,1,1,1,0,1,1}
};

void writeDigit(int digit, int pin_order[7]){
  for(int segment = 0; segment<7; segment++){
    digitalWrite(pin_order[segment], seven_seg_digits[digit][segment]);
  }
}
