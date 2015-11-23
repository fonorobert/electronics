#include "VirtualWire.h"
#include "rfarraytoint.h"

int pinTemp = 4;
int pinHum = 5;
int pinWind = 6;
int pinMetr = 7;
static uint8_t vw_rx_pin = 2;

volatile int ctrlValue = 0;
char * ctrlReading;

volatile int temp = 0;
volatile int hum = 0;
volatile int wind = 0;
static int metr = 2;

int tempStarted = 0;
int humStarted = 0;
int windStarted = 0;
int metrStarted = 0;

int tempState = LOW;
int humState = LOW;
int windState = LOW;
int metrState = LOW;


int blinktime = 500;
int scale[5] = {4000, 2000, 750, 200, 0};

void setup(){
  Serial.begin(9600);
  Serial.println("Weather display with blinking LEDs");

  pinMode(pinTemp, OUTPUT);
  pinMode(pinHum, OUTPUT);
  pinMode(pinWind, OUTPUT);
  pinMode(pinMetr, OUTPUT);

  vw_set_rx_pin(vw_rx_pin);
  vw_setup(1000);
  vw_rx_start();

  attachInterrupt(0, updateValues, RISING);
}

void loop(){
  int time = millis();

  if(ctrlValue == 1){
    Serial.println(ctrlReading);
    ctrlValue = 0;
  }

  if(tempState == LOW) {
    if(time - tempStarted >= scale[temp]){
      digitalWrite(pinTemp, HIGH);
      tempState = HIGH;
      tempStarted = time;
    }
  } else if (tempState == HIGH){
    if(time - tempStarted >= blinktime){
      digitalWrite(pinTemp, LOW);
      tempState = LOW;
      tempStarted = time;
    }
  }

  if(humState == LOW) {
    if(time - humStarted >= scale[hum]){
      digitalWrite(pinHum, HIGH);
      humState = HIGH;
      humStarted = time;
    }
  } else if (humState == HIGH){
    if(time - humStarted >= blinktime){
      digitalWrite(pinHum, LOW);
      humState = LOW;
      humStarted = time;
    }
  }

  if(windState == LOW) {
    if(time - windStarted >= scale[wind]){
      digitalWrite(pinWind, HIGH);
      windState = HIGH;
      windStarted = time;
    }
  } else if (windState == HIGH){
    if(time - windStarted >= blinktime){
      digitalWrite(pinWind, LOW);
      windState = LOW;
      windStarted = time;
    }
  }

  if(metrState == LOW) {
    if(time - metrStarted >= scale[metr]){
      digitalWrite(pinMetr, HIGH);
      metrState = HIGH;
      metrStarted = time;
    }
  } else if (metrState == HIGH){
    if(time - metrStarted >= blinktime){
      digitalWrite(pinMetr, LOW);
      metrState = LOW;
      metrStarted = time;
    }
  }

}

void updateValues(){
  uint8_t msg[VW_MAX_MESSAGE_LEN];
  uint8_t msglength = VW_MAX_MESSAGE_LEN;

  if(vw_get_message(msg, &msglength)){

    int value = rfArrToInt(msg, msglength);

    if (value < 200) {
      value -= 100;
      if(value < 17) {
        temp = 0;
      } else if (value < 20) {
        temp = 1;
      } else if (value < 24) {
        temp = 2;
      } else if (value < 29) {
        temp = 3;
      } else if (value >= 29) {
        temp = 4;
      }
    } else if(value < 300 && value >= 200) {
        value -= 200;
        if (value < 22){
          hum = 0;
        } else if (value < 30) {
          hum = 1;
        } else if (value < 50) {
          hum = 2;
        } else if (value < 70) {
          hum = 3;
        } else if (value >= 70) {
          hum = 4;
        }
    } else if(value >= 300) {
      value -= 300;

      if (value < 5) {
        wind = 0;
      } else if (value < 7) {
        wind = 1;
      } else if (value < 11) {
        wind = 2;
      } else if (value < 15) {
        wind = 3;
      } else if (value >= 15) {
        wind = 4;
      }

    }
  }
}
