#include <ESP8266WiFi.h>
//#include <DNSServer.h>
//#include <ESP8266WebServer.h>
//#include <WiFiManager.h>  
//#include <ESP8266HTTPClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "DHT.h"

#define DHTTYPE DHT11
#define ONE_WIRE_BUS D1 //Pin Sensor Suhu DS18B20
#define DHTPIN D2       //Pin Sensor DHT11
#define LED     D0
#define LED_Proses D3
#define Fan D7
#define Mist D8

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DHT dht(DHTPIN, DHTTYPE);


float suhu=0;
float kelembaban=0;

void setup() {
//============//Koneksi Network//=====================
  Serial.begin(115200);                                  //Serial connection
 // WiFiManager wifiManager;
// wifiManager.resetSettings();
//  wifiManager.autoConnect("Smart Garden","D3elektronika16");
//  Serial.println("connected...yeey :)");
  delay(1000);
  
   sensors.begin();
   Serial.println("Sensor Tes.....\t");
   Serial.println("   ");
   dht.begin();
   pinMode(LED_Proses,OUTPUT);
   pinMode(LED, OUTPUT);
   pinMode(Fan,OUTPUT);
   pinMode(Mist, OUTPUT);
}

void loop() {
digitalWrite(LED, LOW);
digitalWrite(LED_Proses,HIGH);
//==============//Proses Input//=======================
   delay(1000);
   sensors.requestTemperatures();
   suhu=sensors.getTempCByIndex(0)+3;
   float h = dht.readHumidity();
   kelembaban = h-5;

   
   Serial.println("====Baca Data====");
   Serial.print("Suhu : ");
   Serial.print(suhu);
   Serial.println("*C");
   Serial.print("Humidity : ");
   Serial.print(kelembaban);
   Serial.println("%");
   delay(200);
}
