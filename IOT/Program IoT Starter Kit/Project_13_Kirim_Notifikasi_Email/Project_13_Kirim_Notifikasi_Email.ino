/*************************************
 * Program :Project 13 Kirim Notifikasi Email
 * Input : SW1 di pin D2 
 * Output : Email notification
 * Iot Starter Kit Inkubatek
 * www.tokotronik.com
 * ***********************************/
#define BLYNK_MAX_SENDBYTES 1200
#include <ESP8266WiFi.h>

#define BLYNK_PRINT Serial    
#include <BlynkSimpleEsp8266.h>
//ganti dengan kode token yang ada terima di email
char auth[] = "777ef75e90344862a8705f9ded3f508d";
//ganti dengan jaringan dan password WiFi anda
char ssid[] = "FirnasAbe1";
char pass[] = "podowingi";


#define tombol D2 
int tbValue; 

void setup()
{
  Serial.begin(115200);
  delay(10);
  Blynk.begin(auth, ssid, pass);
  pinMode(tombol, INPUT);    
}

void loop()
{
  cek_tombol();
  Blynk.run();
}

// **************************************************/
void cek_tombol(void)
{
  tbValue = digitalRead(tombol);
  if (tbValue) 
  { 
    Serial.println("Tombol ON");
    //ganti dengan alamat email anda , Judul Email, Isi Email   
    Blynk.email("inkubatek@yahoo.com", "IoT Starter Kit", "Tombol Terdeteksi");
    delay(1000);
  }  
}

