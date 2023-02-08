#include <ESP8266WiFi.h>
#include <Wire.h>  // i2C Conection Library
#include <LiquidCrystal_I2C.h>  //i2C LCD Library

//Gunakan define dibawah ini untuk jenis Relay Module HIGH ACTIVE
#define ON 1
#define OFF 0


LiquidCrystal_I2C lcd(0x3F , 16, 2);
 
const char* ssid = "RAJACELL"; //<-Ganti dengan nama jaringan wifi anda 
const char* password = "Rajacellisthebest"; //<- Ganti dengan password wifi anda

//Wiring Relay ke module Nodemcu
const int LED1 = D8; //D8 di ESP Board 

bool value1 = LOW;
bool value2 = LOW;
bool value3 = LOW;
bool value4 = LOW;

WiFiServer server(80); // Wifi PORT

int delayLCD = 750; // delay pergantian text pada LCD 1602 (mS)

void setup() {
  Serial.begin(115200);

 // initialize the LCD
 Wire.begin(2, 0);
 lcd.begin();
  lcd.setCursor (0,0);
  lcd.print("Hello, world!");
  lcd.setCursor (0,1);
  lcd.print("belajarduino.com");
  delay (delayLCD); 
  pinMode(LED1, OUTPUT);  digitalWrite(LED1, LOW);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  lcd.setCursor (0,0);
  lcd.print ("Connecting to...");
  lcd.setCursor (0,1);
  lcd.print (ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    lcd.print (".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  lcd.clear();
  lcd.setCursor (0,0);
  lcd.print (" WiFi connected ");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
  lcd.setCursor (0,1);
  lcd.print (" Server started ");
  delay (2000);
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  lcd.clear();
  lcd.setCursor (0,0);
  lcd.print ("ESP8266 URL ADRS");
  lcd.setCursor (0,1);
  lcd.print (WiFi.localIP());
  delay (2000);
}
 
void loop() {
  
  // Cek jika client sudah terkoneksi dengan jaringan
  WiFiClient client = server.available();
  if (!client) {
  
  lcd.clear();
  lcd.setCursor (0,0);
  lcd.print ("ESP8266 URL ADRS");
  lcd.setCursor (0,1);
  lcd.print (WiFi.localIP());
  lcd.print ("     ");
    return;
  }
  
 html();
 
}

//fungsi untuk membuat tampilan HTML serta mengolah data cliet
void html () {
   // Menunggu Client mengirim data
  Serial.println("new client");
  lcd.clear();
  lcd.setCursor (0,0);
  lcd.print ("Client Send Data");
  while(!client.available()){
    delay(1);
  }
 
  // Program membaca line pertama dari request client
  String request = client.readStringUntil('\r');
  Serial.println(request);
  lcd.setCursor (0,1);
  lcd.print (request);
  delay(1000);
  client.flush();
          
 // Program HTML untuk website
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); 
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<fieldset>");
  client.println("<font color = redq>");
  client.print("Control 4 LED Via Wifi");
  client.println("</font>");
  client.println("</fieldset>");
  client.println("<br><br>");

  // Control LED 1
  if (request.indexOf("/status1=1") != -1)  {
    digitalWrite(LED1, ON);
    value1 = HIGH;
      lcd.setCursor(0,0);
      lcd.print("LED1 set to ON  ");
      lcd.setCursor(0,1);
      lcd.print("by Client Reques");
      delay (delayLCD);
    }
  if (request.indexOf("/status1=0") != -1)  {
    digitalWrite(LED1, OFF);
    value1 = LOW;
      lcd.setCursor(0,0);
      lcd.print("LED1 set to OFF ");
      lcd.setCursor(0,1);
      lcd.print("by Client Reques");
      delay (delayLCD);
     }
     if(value1==HIGH){
      client.println("<br><br>");
      client.print("status1=1");
      }
     if(value1==LOW){
      client.println("<br><br>");
      client.print("status1=0");
      }

  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
  lcd.setCursor(0,1);
  lcd.print("Client Disconect");
  delay(1000);
}
