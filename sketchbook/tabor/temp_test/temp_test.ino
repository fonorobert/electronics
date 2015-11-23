/* Sensor test sketch
  for more information see http://www.ladyada.net/make/logshield/lighttemp.html
  */

#define aref_voltage 5

//TMP36 Pin Variables
int tempPin = A0;        //the analog pin the TMP36's Vout (sense) pin is connected to
                        //the resolution is 10 mV / degree centigrade with a
                        //500 mV offset to allow for negative temperatures
int tempReading;        // the analog reading from the sensor

void setup(void) {
  Serial.begin(9600);
}


void loop(void) {

  tempReading = analogRead(tempPin);

  Serial.print("Temp reading = ");
  Serial.print(tempReading);     // the raw analog reading

  // converting that reading to voltage, which is based off the reference voltage
  float voltage = tempReading;
  voltage = voltage * (aref_voltage / 1023.0);

  // print out the voltage
  Serial.print(" - ");
  Serial.print(voltage);
  Serial.println(" volts");

  // now print out the temperature
  float temperatureK = voltage * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((volatge - 500mV) times 100)

  float temperatureC = temperatureK - 273.15;
  /*Serial.print(temperatureK); Serial.println(" degrees K");*/
  Serial.print(temperatureC); Serial.println(" degrees C");

  delay(1000);
}
