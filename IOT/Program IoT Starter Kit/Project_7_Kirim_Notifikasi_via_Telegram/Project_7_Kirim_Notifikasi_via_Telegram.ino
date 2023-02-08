/*************************************
 * Program :Project 7 Kirim Notifikasi ke Telegram
 * Input : SW1 di pin D2
 * Output : Telegram
 * Iot Starter Kit Inkubatek
 * www.tokotronik.com
 * ***********************************/

#include <UniversalTelegramBot.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

//------- WiFi Settings -------
char ssid[] = "FirnasAbe";       // WiFi
char password[] = "podowingi";  // password WiFi
// ------- Telegram config --------
#define BOT_TOKEN "679994158:BCRX6dQW3RKlmnhgfRtZSv7T-GHJd4N4"  // Bot Token Anda
#define CHAT_ID "212967234" // Chat ID Anda
#define tombol D2
WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);
String ipAddress = "";
volatile bool tombolFlag = false;
int button;
//===================================
void setup() {
  Serial.begin(115200);
  pinMode(tombol, INPUT);   
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
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
  ipAddress = ip.toString();
}

//=====================================================
void sendTelegramMessage() {    
  Serial.println("Kirim pesan ke Telegram");
  String message = "Tombol ditekan ....";
  message.concat("\n");
  message.concat("IoT Starter Kit Inkubatek"); 
  message.concat("\n");
  if(bot.sendMessage(CHAT_ID, message, "Markdown")){
    Serial.println("Pesan telah dikirim ke TELEGRAM");
  }
  else Serial.println("gagal kirim..");
  tombolFlag = false;
  
}
//=====================================================
void loop() { 
  button = digitalRead(tombol);
  if(button==HIGH){
     Serial.println("Tombol ditekan");  
     while(button = digitalRead(tombol)); //nunggu low
     sendTelegramMessage();
     delay(500);
  } 
}
