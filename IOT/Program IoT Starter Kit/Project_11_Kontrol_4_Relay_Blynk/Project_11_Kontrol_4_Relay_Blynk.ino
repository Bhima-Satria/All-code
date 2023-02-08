/*************************************
 * Program :Project 11 Kontrol 4 Relay via Blynk
 * Input :  
 * Output : Relay
 * Iot Starter Kit Inkubatek
 * www.tokotronik.com
 * ***********************************/
 
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Ganti dengan token anda yang dikirim via email.
char auth[] = "-LVDfN9TziO0Hfjdnc1ypbm53yzXHRsW";

// Ganti dengan WiFi dan Password anda
char ssid[] = "Zahra wifi";
char pass[] = "setyobudi1997";

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
}

