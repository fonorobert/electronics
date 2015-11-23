int diode = A0;

void setup(){
  Serial.begin(9600);
}

void loop(){
    int val = analogRead(diode);
    Serial.println(val);
    delay(20);
}
