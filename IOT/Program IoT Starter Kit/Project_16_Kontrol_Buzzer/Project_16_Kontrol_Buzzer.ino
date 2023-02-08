/*************************************
 * Program :Project 16 Kontrol Buzzer
 * Input : - 
 * Output : Buzzer di D1
 * Iot Starter Kit Inkubatek
 * www.tokotronik.com
 * ***********************************/
 
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
//Ganti dengan Token anda
char auth[] = "6d2c7f338e0b498a87c8ec4fbaf07406";

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

