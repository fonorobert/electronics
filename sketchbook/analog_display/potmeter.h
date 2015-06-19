int potmeter(int pin, int map_to[2]){
  int sensorValue = analogRead(pin);
  int result = map(sensorValue, 0, 1023, map_to[0], map_to[1]);
  delay(2);
  return result;
}
