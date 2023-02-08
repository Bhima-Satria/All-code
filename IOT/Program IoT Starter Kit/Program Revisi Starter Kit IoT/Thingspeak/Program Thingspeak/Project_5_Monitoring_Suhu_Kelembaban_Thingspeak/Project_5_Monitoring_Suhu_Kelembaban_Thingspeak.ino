/*************************************
 * Program :Project 5 Monitoring Suhu Kelembaban Thingspeak
 * Input : DHT11 di pin D5
 * Output : Grafik Thingspeak
 * Iot Starter Kit Inkubatek
 * www.tokotronik.com
 *************************************
 * KONEKSI NODEMCU dg DHT22
 * NODEMCU  |   DHT22
 *    D3   -->    1
 *    +5   -->    2
 *   GND   -->    3
 *************************************/
#include <DHT.h>
#include "ThingSpeak.h"
#include <ESP8266WiFi.h>

char ssid[] = "namaWiFi"; 
char pass[] = "passwordWiFi";  
WiFiClient  client;

unsigned long myChannelNumber = 1029000; 
const char * myWriteAPIKey = "4XYI1SXXXXXXXXXX";

#define DHTPIN D3 //pin out dht11
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

byte delaySend;

void setup() {
  Serial.begin(115200);  
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);  
  if(WiFi.status() != WL_CONNECTED){
    Serial.println(" ");
    Serial.println(" ");
    Serial.print("Attempting to connect to SSID: ");    
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  
      Serial.print(".");
      delay(5000);    
    }
    Serial.println("\nConnected.");
  }
  delay(2000);
  dht.begin();
}
//=======================
void loop() {  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("DHT22 tidak terbaca... !");
    return;
  }  
  delaySend++;
  if (delaySend<20)return;
  ThingSpeak.setField(1,t);
  ThingSpeak.setField(2,h);
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  } 
  delaySend=0;
  delay(3000);  
}
