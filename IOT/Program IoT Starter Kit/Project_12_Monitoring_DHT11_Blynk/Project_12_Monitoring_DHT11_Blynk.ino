/*************************************
 * Program :Project 12 Monitoring DHT11 Blynk
 * Input : DHT11 di pin D5 
 * Output : Relay
 * Iot Starter Kit Inkubatek
 * www.tokotronik.com
 * ***********************************/
#define BLYNK_PRINT Serial 
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <SimpleTimer.h>
#define DHTPIN D5 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

SimpleTimer timer;

float humi, temp; 
// Ganti dengan kode token anda
char auth[] = "123a369f2894c55b219aa4def71346e"; 
// Ganti dengan WiFi dan Password anda
char ssid[] = "FirnasAbe";
char pass[] = "hamasfahreza";

void setup()
{
  Serial.begin(115200); 
  delay(10);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000, sendData);
}

void sendData()
{  
  humi = dht.readHumidity();
  temp = dht.readTemperature();
  Blynk.virtualWrite(10, temp);//virtual input V10 di Blynk (suhu)
  Blynk.virtualWrite(11, humi);//virtual input V11 di Blynk (kelembaban)
}

void loop()
{
  Blynk.run();
  timer.run();
}
