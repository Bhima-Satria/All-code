/*************************************
 * Program :Project 14 Deteksi Kebocoran Gas
 * Input : MQ2 di pin D5
 * Output : Email notification
 * Iot Starter Kit Inkubatek
 * www.tokotronik.com
 * ***********************************/
 
#include <ESP8266WiFi.h>
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <BlynkSimpleEsp8266.h>
char auth[] = "1928e00202647eb833bc78cb26b9d84";

/* Ganti dengan ssid dan password WiFi anda */
char ssid[] = "FirnasAbe";
char pass[] = "podowingi";

#define MQ2Pin D5 
int MQ2Value; 

void setup()
{
  Serial.begin(115200);
  delay(10);
  Blynk.begin(auth, ssid, pass);
  pinMode(MQ2Pin, INPUT);    
}

void loop()
{
  getMQ2Value();
  Blynk.run();
}

// **************************************************/
void getMQ2Value(void)
{
  MQ2Value = digitalRead(MQ2Pin);
  if (!MQ2Value) 
  { 
    Serial.println("==>Gas terdeteksi");
    Blynk.notify("Kebocoran Gas terdeteksi.....!");  
    delay(1000);
  }
  
}

