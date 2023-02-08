/*************************************
 * Program :Project 8 Sistem Keamanan Rumah sensor PIR ke Telegram
 * Input : Sensor PIR di pin D5 
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
#define PIR_Sensor D5
WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);
String ipAddress = "";
volatile bool PIRFlag = false;
int sensor;
//===================================
void setup() {
  Serial.begin(115200);
  pinMode(PIR_Sensor, INPUT);  
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(1000);  
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
//==================================================
void sendTelegramMessage() {
  Serial.println("Kirim pesan ke Telegram");
  delay(200);
  String message = "Sensor mendeteksi objek ....";
  message.concat("\n");
  message.concat("WASPADA !!!"); 
  message.concat("\n");
  message.concat("IoT Starter Kit Inkubatek"); 
  message.concat("\n");
  if(bot.sendMessage(CHAT_ID, message, "Markdown")){
    Serial.println("Pesan telah dikirim ke TELEGRAM");
  }
  else Serial.println("gagal kirim..");  
}
//=====================================================
void loop() { 
  sensor = digitalRead(PIR_Sensor);
  if(sensor==HIGH){
     delay(500);
     Serial.println("Sensor PIR Aktif");  
     while(sensor = digitalRead(PIR_Sensor)); //nunggu low
     sendTelegramMessage();
     delay(2000);
  }   
}
