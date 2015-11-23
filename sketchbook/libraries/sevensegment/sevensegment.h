#include "Arduino.h"
int seven_seg_digits[11][7]{
  {1,1,1,1,1,1,0},
  {0,1,1,0,0,0,0},
  {1,1,0,1,1,0,1},
  {1,1,1,1,0,0,1},
  {0,1,1,0,0,1,1},
  {1,0,1,1,0,1,1},
  {1,0,1,1,1,1,1},
  {1,1,1,0,0,0,0},
  {1,1,1,1,1,1,1},
  {1,1,1,1,0,1,1},
  {0,0,0,0,0,0,1}
};

// {a,b,c,d,e,f,g}

//   a
//   _
// f|_|b
// e|_|c
//   d

void writeDigit(int digit, int pin_order[7]){
  for(int segment = 0; segment<7; segment++){
    digitalWrite(pin_order[segment], seven_seg_digits[digit][segment]);
  }
}

void writeNumber(int number, int pin_order[7], int ground[2], int timer){
  int first_digit;
  int second_digit;
  if(number<100){
    first_digit = int(floor(number/10));
    second_digit = number - first_digit*10;
  }
  else {
    first_digit = 10;
    second_digit = 10;
  }
  for(int i=0; i<timer;i++){
    writeDigit(first_digit, pin_order);
    digitalWrite(ground[0], LOW);
    digitalWrite(ground[1], HIGH);
    delay(10);
    writeDigit(second_digit, pin_order);
    digitalWrite(ground[0], HIGH);
    digitalWrite(ground[1], LOW);
    delay(10);
  }
}
