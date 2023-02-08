/*************************************
 * Program :Project 15 Kontrol LED RGB
 * Input : 
 * Output : RGB LED
 * Iot Starter Kit Inkubatek
 * www.tokotronik.com
 * ***********************************/
 
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
//Ganti dengan Token anda
char auth[] = "ae604d9ca16244aea483564013a119e0";

// Ganti dengan WiFi anda
char ssid[] = "FirnasAbe";
char pass[] = "podowingi";

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);  
}

void loop()
{
  Blynk.run(); 
}
