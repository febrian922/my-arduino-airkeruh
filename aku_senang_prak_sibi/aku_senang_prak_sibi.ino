int lightPin = A0; // select the input pin for the ldr
int digitalValue = 0; // variable to store the value coming from the sensor
float analogVoltage = 0.00;
float restLDR = 0.00;
float lux = 0.00;
void setup() {
 Serial.begin(9600);
}
void loop() {
 digitalValue = analogRead(lightPin);// read the value from the analog channel
 analogVoltage = (digitalValue * 5.00)/1023.00;
 restLDR = analogVoltage*1000/(5-analogVoltage);
 lux = 30000-analogVoltage * 6000.0; //convert the analog data to light intensity (not exact eq. just for example)
 Serial.print("Light intensity: ");
 Serial.println(lux); //send the data through serial interface
 delay(1000);
}
