#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  //0x27 is the i2c address, while 16 = columns, and 2 = rows.

void setup() {
  pinMode(A0, INPUT); 
  lcd.init();                 //Init the LCD
  lcd.backlight();            //Activate backlight     
  lcd.home(); 
}
void loop() {

  int sensorValue = analogRead(A0);// read the input on analog pin A0:
  float voltage = sensorValue * (10.0 / 1024.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Turbidity: ");
  lcd.print(voltage);
  lcd.print("  ");
  lcd.setCursor(0,1);
  if(voltage<1.25)            lcd.print("Water Very Dirty");
  if(voltage>=1.25 && voltage<3.0) lcd.print("Water Dirty");
  if(voltage>=3.2 && voltage<3.7) lcd.print("Water Norm Clean");
  if(voltage>=3.7)           lcd.print("Water Very Clean");

  delay(500);
}
