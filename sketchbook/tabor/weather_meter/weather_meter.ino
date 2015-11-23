#include "VirtualWire.h"
#include "temp.h"
#include "hum.h"
#include "wind.h"

#define aref_voltage 5

int tempPin = A0;
int humPin = A1;
int windPin = A2;
static uint8_t vw_tx_pin = 2;

void setup(void) {
  Serial.begin(9600);
  vw_set_tx_pin(vw_tx_pin);
  vw_setup(1000);
}


void loop(void) {

  int temp = tempMeter(tempPin, aref_voltage);
  delay(2);
  int hum = humMeter(humPin, aref_voltage);
  delay(2);
  /*int wind = windMeter(windPin, aref_voltage);*/

  // temp = temp + 100;
  // hum = hum + 200;

  String tempStr;
  String humStr;

  tempStr = String(temp);
  humStr = String(hum);

  char tempMsg[4];
  char humMsg[4];

  tempStr.toCharArray(tempMsg, 4);
  humStr.toCharArray(humMsg, 4);

  vw_send((uint8_t *)tempMsg, sizeof(tempMsg)/sizeof(tempMsg[0]));
  vw_wait_tx();

  delay(20);

  vw_send((uint8_t *)humMsg, sizeof(humMsg)/sizeof(humMsg[0]));
  vw_wait_tx();

  Serial.print("temp: ");
  Serial.print(tempMsg);
  Serial.println();

  Serial.print("hum: ");
  Serial.print(humMsg);
  Serial.println();

  // Serial.println(tempMsg);
  // Serial.println(humMsg);
  /*Serial.println(wind);*/
  /*delay(1000);*/
/*
  Serial.println();*/
}
