// Include the libraries we need
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); //The LCD address and size. You can change according you yours
// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS D3 //pin for sensor
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
#define RELAY  D5
/*
   The setup function. We only start the sensors here
*/
// Initialize Wifi connection to the router
char ssid[] = "IPB-GUEST";     // diisi nama wifi
char password[] = "makanayam123"; // diisi password wifi

// Initialize Telegram BOT
#define BOTtoken "5744694088:AAEQL-DE8s-9BIyZKdfuJmlGHGGUdepGK3k" // diisi Token Bot (Dapat dari Telegram Botfather)

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

//Checks for new messages every 1 second.
int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "") from_name = "Guest";
 
    //Cek Pembacaan Sensor suhu
    if (text == "/statussuhu") {
      int tempC = sensors.getTempCByIndex(0);
       String temp = "Suhu saat ini : ";
       temp +=" \n";
       temp += int(tempC);
       temp +=" *C  |  ";
       temp += int(DallasTemperature::toFahrenheit(tempC));
       temp +=" *F  ";
       
      bot.sendMessage(chat_id,temp, "");
    }
    
    //Cek Command untuk setiap aksi
    if (text == "/start") {
      String welcome = "Welcome  " + from_name + ".\n";
      welcome += "/statussuhu : Status Suhu\n";
      welcome += "/On : Kipas menyala\n";
      welcome += "/Off : Kipas mati\n";
      bot.sendMessage(chat_id, welcome, "Markdown");
    }
    if (text == "/On") //Perintah dari telegram ke perangkat
    {  
      digitalWrite(RELAY, LOW );  
      Serial.println("message received"); 
    
      bot.sendMessage(chat_id, "Kipas Menyala");  //Balasan dari perangkat ke Bot Telegram
    }  
    else if (text == "/Off") //Perintah dari telegram ke perangkat
    {  
      digitalWrite(RELAY, HIGH);  
      Serial.println("message received");  
      bot.sendMessage(chat_id, "Kipas Mati");  //Balasan dari perangkat ke Bot Telegra
    }
  }
}

void setup(void)
{
  // start serial port
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library");
  // Start up the library
  sensors.begin();
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("DS18B20 TEST!");
  delay(2000);
  lcd.clear();
  client.setInsecure();
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  
  // relay
  pinMode(RELAY, OUTPUT);
  pinMode(RELAY, HIGH);
  
  // attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
}

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}


/*
   Main function, get and show the temperature
*/
void loop(void)
{
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  //
  // After we got the temperatures, we can print them here.
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
  int tempC = sensors.getTempCByIndex(0);
  // Check if reading was successful
  if (tempC != DEVICE_DISCONNECTED_C)
  {
    Serial.print("Temperature for the device 1 (index 0) is: ");
    Serial.println(tempC);
    lcd.setCursor(0, 0);
    lcd.print("Temperature:");
    lcd.setCursor(0, 1);
    lcd.print(tempC);
    lcd.print((char)223);
    lcd.print("C");
    lcd.print(" | ");
    lcd.print(DallasTemperature::toFahrenheit(tempC));
    lcd.print(" F");
  }
  else
  {
    Serial.println("Error: Could not read temperature data");
  }
   if (tempC < 30){
  digitalWrite(RELAY, HIGH);
  }
  else
  {
  digitalWrite(RELAY, LOW);
  }
 
    if (millis() > lastTimeBotRan + botRequestDelay)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    lastTimeBotRan = millis();
  }
}
