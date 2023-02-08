/*************************************
 * Program :Project 8 Sistem Keamanan Rumah sensor PIR ke Telegram
 * Input : Sensor PIR di pin D5 
 * Output : Telegram
 * Iot Starter Kit Inkubatek
 * www.tokotronik.com
 * ***********************************/
#include "CTBot.h"
CTBot myBot;

String ssid = "Ardutech";     // REPLACE mySSID WITH YOUR WIFI SSID
String pass = "12345678"; // REPLACE myPassword YOUR WIFI PASSWORD, IF ANY
String token = "1048951618:AAGmdVvk5MmlTUAa7e1Epf9vVUC21SbH63s";   // REPLACE myToken WITH YOUR TELEGRAM BOT TOKEN
long chartIDbot = 780527635;//sesuaikan ChartID anda

int PIRPIN = D5;

void setup() {
 Serial.begin(115200);
 Serial.println();
 Serial.println();
 Serial.println("Starting TelegramBot...");
 myBot.wifiConnect(ssid, pass);
 myBot.setTelegramToken(token);
	// check if all things are ok
 if (myBot.testConnection())	Serial.println("\ntestConnection OK");
 else Serial.println("\ntestConnection NOK");
 pinMode(PIRPIN, INPUT_PULLUP);
}

void loop() {
	TBMessage msg;
  if(digitalRead(PIRPIN)==HIGH){    
    msg.text="Sensor PIR Aktif";
    Serial.println(msg.text);
    while(digitalRead(PIRPIN)){
      delay(100);
    }
    myBot.sendMessage(chartIDbot, msg.text);  // notify the sender
	}
	delay(1000);
}
