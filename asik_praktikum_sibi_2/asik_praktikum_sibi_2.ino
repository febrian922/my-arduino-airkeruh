#include "DHT.h"
 #define DHTPIN 2 
 #define DHTTYPE DHT11 // DHT 11
 DHT dht(DHTPIN, DHTTYPE);
 int lightPin = A0; // select the input pin for the potentiometer
 int digitalValue = 0; // variable to store the value coming from the sensor
 float analogVoltage = 0.00;
 float restLDR = 0.00;
 float lux = 0.00;
 void setup() {
 Serial.begin(9600);
 dht.begin();
 }
 void loop() {
 delay(2000);
 // Read humidity
 float h = dht.readHumidity();
 // Read temperature as Celsius (the default)
 float t = dht.readTemperature();
 digitalValue = analogRead(lightPin);// read the value from the analog channel
 analogVoltage = (digitalValue * 5.00)/1023.00;
 restLDR = analogVoltage*1000/(5-analogVoltage);
 lux = 30000-analogVoltage * 6000.0; //convert the analog data to light intensity (not exact eq. just for example)
 Serial.println("---------------------");
 Serial.print("Humidity: ");
 Serial.print(h);
 Serial.print("%\n");
 Serial.print("Temperature: ");
 Serial.print(t);
 Serial.print("\n");
 Serial.print("Light Intensity: ");
 Serial.println(lux);
 Serial.print("\n");
}
refresinpi
