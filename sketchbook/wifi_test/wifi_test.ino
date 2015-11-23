#include "ESP8266.h"
#include "SoftwareSerial.h"

#define SSID "SzoszoHome"
#define PASSWORD "11szoszo2358"
#define HOST_NAME "192.168.1.100"
#define HOST_PORT (8000)

SoftwareSerial mySerial(3,2);
ESP8266 wifi(mySerial);

void setup(){
    mySerial.begin(9600);
    Serial.begin(9600);
    bool setOprToStationSoftAP = wifi.setOprToStationSoftAP();
    bool joinAP = wifi.joinAP(SSID, PASSWORD);
    bool disableMUX = wifi.disableMUX();

}

void loop(){
  uint8_t buffer[1024] = {0};
  wifi.createTCP(HOST_NAME, HOST_PORT);
  char *hello = "GET / HTTP/1.1\r\nHost: 192.168.1.100\r\nConnection: close\r\n\r\n";
  wifi.send((const uint8_t*)hello, strlen(hello));

  uint32_t len = wifi.recv(buffer, sizeof(buffer), 10000);
  wifi.releaseTCP();

  delay(10000);
}
