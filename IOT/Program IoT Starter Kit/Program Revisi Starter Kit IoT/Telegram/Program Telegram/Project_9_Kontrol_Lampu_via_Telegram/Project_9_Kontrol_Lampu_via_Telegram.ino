/*************************************
 * Program :Project 9 Kontrol Lampu via Telegram
 * Input :  
 * Output : Relay
 * Iot Starter Kit Inkubatek
 * www.tokotronik.com
 * ***********************************/
#include "CTBot.h"
CTBot myBot;
#define RL1 D1
#define RL2 D2
#define RL3 D5
#define RL4 D6
String ssid = "Ardutech";     
String pass = "12345678"; 
String token = "1048951618:AAGmdVvk5MmlTUAa7e1Epf9vVUC21SbH63s";   // REPLACE myToken WITH YOUR TELEGRAM BOT TOKEN
String str;                                          
TBMessage msg;

void setup() {
 pinMode(RL1, OUTPUT);  
 pinMode(RL2, OUTPUT);
 pinMode(RL3, OUTPUT);
 pinMode(RL4, OUTPUT);
 digitalWrite(RL1,HIGH);
 digitalWrite(RL2,HIGH);
 digitalWrite(RL3,HIGH);
 digitalWrite(RL4,HIGH);
 Serial.begin(115200);
 Serial.println();
 Serial.println();
 Serial.println("Starting TelegramBot..."); 
 myBot.wifiConnect(ssid, pass);
 myBot.setTelegramToken(token);
 if (myBot.testConnection())
  Serial.println("Connection OK");
 else
  Serial.println("Connection Not OK");  
}
void loop() { 
  if (myBot.getNewMessage(msg)) {
    //================ Relay 1 =====================
    if (msg.text.equalsIgnoreCase("1 on")) {              
      digitalWrite(RL1, LOW);                               
      myBot.sendMessage(msg.sender.id, "Lampu 1 ON");  
    }
    else if (msg.text.equalsIgnoreCase("1 off")) {        
      digitalWrite(RL1, HIGH);                              
      myBot.sendMessage(msg.sender.id, "Lampu 1 OFF"); 
    }   
   //================ Relay 2 =====================
    if (msg.text.equalsIgnoreCase("2 on")) {              
      digitalWrite(RL1, LOW);                               
      myBot.sendMessage(msg.sender.id, "Lampu 2 ON");  
    }
    else if (msg.text.equalsIgnoreCase("2 off")) {        
      digitalWrite(RL1, HIGH);                              
      myBot.sendMessage(msg.sender.id, "Lampu 2 OFF"); 
    }
    //================ Relay 3 =====================
   if (msg.text.equalsIgnoreCase("3 on")) {              
      digitalWrite(RL3, LOW);                               
      myBot.sendMessage(msg.sender.id, "Lampu 3 ON");  
    }
    else if (msg.text.equalsIgnoreCase("3 off")) {        
      digitalWrite(RL3, HIGH);                              
      myBot.sendMessage(msg.sender.id, "Lampu 3 OFF"); 
    }
    //================ Relay 4 =====================
   if (msg.text.equalsIgnoreCase("4 on")) {              
      digitalWrite(RL4, LOW);                               
      myBot.sendMessage(msg.sender.id, "Lampu 4 ON");  
    }
    else if (msg.text.equalsIgnoreCase("4 off")) {        
      digitalWrite(RL4, HIGH);                              
      myBot.sendMessage(msg.sender.id, "Lampu 4 OFF"); 
    }
  } 
  delay(500);
}
