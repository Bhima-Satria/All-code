/*************************************
 * Program :Project 4 Monitoring Suhu Thingspeak
 * Input : LM35 di A0
 * Output : Grafik Thingspeak
 * Iot Starter Kit Inkubatek
 * www.tokotronik.com
 * ***********************************/
#include "ThingSpeak.h"
#include <ESP8266WiFi.h>

char ssid[] = "Ardutech";  // ganti dg SSID anda 
char pass[] = "12345678";     // ganti dg password SSID anda
WiFiClient  client;

unsigned long myChannelNumber = 1029000; //ganti dg Channel ID Thingspeak anda
const char * myWriteAPIKey = "4XYI1SXXXXXXXXXX";//ganti dengan Write API Key

int analogValue;
float millivolts,celsius;
void setup() {
  Serial.begin(115200);  // Inisialisasi serial
  WiFi.mode(WIFI_STA); 
  ThingSpeak.begin(client);  // Inisialisasi ThingSpeak 
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");    
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  } 
}
//=======================
void loop() {  
  analogValue = analogRead(A0);
  millivolts = (analogValue/1024.0) * 3300; 
  celsius = millivolts/10;   
  Serial.print("Suhu:");
  Serial.print(celsius); 
  Serial.println("C");
  int x = ThingSpeak.writeField(myChannelNumber, 1, celsius, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  } 
  delay(20000); // tunggu 20 detik untuk update 
}
