#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <OneWire.h>
#include <Wire.h>
#include <DallasTemperature.h>
#include "DHT.h" 
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x3f, 16, 2);
String lastkontrol="1";
String kontrol ;
void setup() 
{
    pinMode(LED_BUILTIN, OUTPUT);
    Wire.begin(D4, D3);
    lcd.begin();
    Serial.begin(115200);
    delay(100);
    lcd.print("Connecting....");
    
    
  WiFiManager wifiManager;
  //wifiManager.resetSettings();  
  wifiManager.autoConnect("Sharing IoT","12345678");
  Serial.println("connected...yeey :)");
  delay(1000);

  WiFi.mode(WIFI_STA);
  wifiManager.autoConnect("AutoConnectAP");
  Serial.println("connected...yeey :)");
   
   ArduinoOTA.setPassword((const char *)"123");
   ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_SPIFFS
      type = "filesystem";
    }

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
 
void loop() 
{
  proses();
}

void proses() 
{
  ArduinoOTA.handle(); 
  digitalWrite(LED_BUILTIN, HIGH);
  float C = 45;
 
  if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status

   HTTPClient http;                      //deklarasi object HTTP Client. 
   
   http.addHeader("Content-Type", "text/plain");  //Specify content-type header
   String postStr ="http://api.thingspeak.com/channels/808744/fields/1.json?api_key=95A14G7GECR3WH5Y&results=2";          
   //String postStr1="http://api.thingspeak.com/update?api_key=TM8YCX58UNBP1C9M&field1="+String(C)+"&field2="+String(lastkontrol);
    
   http.begin(postStr);                   //tujuan 
   int httpCode = http.GET();            //Mengirim Permintaan
   String payload = http.getString();   //Mendapat Respon Dari proses
  
 //  http.begin(postStr1);                   //tujuan 
 //  int httpCode1 = http.POST(postStr1);   //Mengirim Permintaan
 //  String payload1 = http.getString();   //Mendapat Respon Dari proses
 
Serial.print (payload);   
kontrol = payload.substring(367,368);
String data = payload.substring(291,296);

  // Serial.print (postStr);
  if (lastkontrol == "1") {
    lcd.setCursor(0,0);
    lcd.clear();
    lcd.print("Lampu Menyala");
    digitalWrite(LED_BUILTIN, LOW);
    }  
  else if (lastkontrol =="0") {
    lcd.setCursor(0,0);
    lcd.clear();
    lcd.print("Lampu Mati");
    digitalWrite(LED_BUILTIN, HIGH);
    }

  else if  (kontrol !="1" && kontrol  !="0"){
    kontrol = kontrol;
  }
lastkontrol=kontrol;

   lcd.setCursor(0,1);
   lcd.print("Data :");
   lcd.print(data);
   Serial.println(data);
   Serial.println(kontrol);
   
   http.end();  //Close connection
  }
  else{ 
  Serial.println("Error in WiFi connection");
  }
delay(15000);

}
