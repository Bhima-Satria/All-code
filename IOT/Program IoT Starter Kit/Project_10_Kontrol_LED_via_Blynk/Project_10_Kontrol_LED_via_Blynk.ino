/*************************************
 * Program :Project 10 Kontrol LED via Blynk
 * Input :  
 * Output : LED di D5
 * Iot Starter Kit Inkubatek
 * www.tokotronik.com
 * ***********************************/
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Ganti dengan tokedn anda yang dikirim via email.
char auth[] = "ee2ba9a5b0aa438cb697c4f9846e4f5f";

// Ganti dengan WiFi dan Password anda
char ssid[] = "FirnasAbe";
char pass[] = "podowingi1";

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
}

