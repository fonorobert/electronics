int led = 7;
int blinktime = 500;
int timer[5] = {4000, 2000, 750, 200, 0};
int step = 2;

void setup(){
  Serial.begin(9600);
  Serial.println("Blink serial test");
  pinMode(led, OUTPUT);
}

void loop(){
  if(Serial.available()){
    int num = Serial.parseInt();
    Serial.println(num);
    step = num;
  }
  Serial.print("step:");
  Serial.println(step);
  Serial.println(timer[step]);
  delay(timer[step]);
  digitalWrite(led, HIGH);
  delay(blinktime);
  digitalWrite(led, LOW);

}
