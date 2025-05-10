String onoff; 
void setup() {
 Serial.begin(9600); 
 pinMode(4, OUTPUT);
}
void loop() {
 if (Serial.available() > 0) {
 onoff = Serial.readStringUntil('\n');
 if (onoff == String("H")) {
 digitalWrite(4, HIGH);
 }
 if (onoff == String("L")) {
 digitalWrite(4, LOW); 
 }
 }
}
