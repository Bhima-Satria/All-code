/*************************************
 * Program :Project 9 Kontrol Lampu via Telegram
 * Input :  
 * Output : Relay
 * Iot Starter Kit Inkubatek
 * www.tokotronik.com
 * ***********************************/
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <TelegramBot.h>

#define RL1 D1
#define RL2 D2
#define RL3 D5
#define RL4 D6

// Sesuaikan dengan jaringan anda
const char* ssid     = "FirnasAbe"; // ganti dengan WiFi anda
const char* password = "podowingi";//ganti dengan password anda

// ganti dengan Token anda
const char BotToken[] = "8890yu158:AAEMX7bQ03RQOnjfrwWqjZN2vU5-VNJd7T4";

WiFiClientSecure net_ssl;
TelegramBot bot (BotToken, net_ssl);
 
void setup() 
{  
 pinMode(RL1, OUTPUT);  
 pinMode(RL2, OUTPUT);
 pinMode(RL3, OUTPUT);
 pinMode(RL4, OUTPUT);
 digitalWrite(RL1,HIGH);
 digitalWrite(RL2,HIGH);
 digitalWrite(RL3,HIGH);
 digitalWrite(RL4,HIGH);
 delay(500);
 Serial.begin(115200);  
 
 delay(3000);  
 
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100); 
 Serial.print("Connecting Wifi: ");  
 Serial.println(ssid);  
 WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
 Serial.println("");  
 Serial.println("WiFi connected");  
 delay(1000);
 bot.begin();  
 
}  
void loop() 
{  
 message m = bot.getUpdates(); // Read new messages 
 //============================== 
 if (m.text.equals("1 on")){  
   digitalWrite(RL1,LOW);   
   bot.sendMessage(m.chat_id, "Lampu 1 ON"); 
   delay(1000); 
 }  
 else if (m.text.equals("1 off")){  
   digitalWrite(RL1,HIGH);   
   bot.sendMessage(m.chat_id, "Lampu 1 OFF");  
   delay(1000); 
 }  

 //===============================  
 else if (m.text.equals("2 on")){  
   digitalWrite(RL2,LOW);   
   bot.sendMessage(m.chat_id, "Lampu 2 ON");  
   delay(1000); 
 }  
 else if (m.text.equals("2 off")){  
   digitalWrite(RL2,HIGH);   
   bot.sendMessage(m.chat_id, "Lampu 2 OFF");  
   delay(1000); 
 }  
 
//===============================  
 else if (m.text.equals("3 on")){  
   digitalWrite(RL3,LOW);   
   bot.sendMessage(m.chat_id, "Lampu 3 ON");  
   delay(1000); 
 }  
 else if (m.text.equals("3 off")){  
   digitalWrite(RL3,HIGH);   
   bot.sendMessage(m.chat_id, "Lampu 3 OFF");  
   delay(1000); 
 } 
//=============================== 

 else if (m.text.equals("4 on")){  
   digitalWrite(RL4,LOW);   
   bot.sendMessage(m.chat_id, "Lampu 4 ON");  
   delay(1000); 
 }  
 else if (m.text.equals("4 off")){  
   digitalWrite(RL4,HIGH);   
   bot.sendMessage(m.chat_id, "Lampu 4 OFF"); 
   delay(1000);  
 } 
 
}  
