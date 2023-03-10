//Program khusus board esp8266 (Nodemcu)

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Arduino_JSON.h>

const char* ssid = "Workshop_Batujajar"; //masukkan ssid
const char* password = "Workshop2020"; //masukkan password

const long interval = 10; //5000
unsigned long previousMillis = 0;

int board = 1;

void setup () {

  Serial.begin(115200);
  WiFi.begin(ssid, password); 

  while (WiFi.status() != WL_CONNECTED) {

    delay(1000);
    Serial.println("Connecting..");

  }

  if(WiFi.status() == WL_CONNECTED){
    Serial.println("Connected!!!");
  }
  else{
    Serial.println("Connected Failed!!!");
  }

}

void loop() {

    HTTPClient http;
    http.begin("http://192.168.1.7/esp_iot/proses.php?board="+String(board)); 
    int httpCode = http.GET();

    unsigned long currentMillis = millis();
  
  if(currentMillis - previousMillis >= interval) {
      if (WiFi.status() == WL_CONNECTED) {
        if (httpCode > 0) {
            String payload = http.getString();
            JSONVar myObject = JSON.parse(payload);
    
            Serial.print("JSON object = ");
            Serial.println(myObject);
        
            JSONVar keys = myObject.keys();
        
            for (int i = 0; i < keys.length(); i++) {
                JSONVar value = myObject[keys[i]];
                Serial.print("GPIO: ");
                Serial.print(keys[i]);
                Serial.print(" - SET to: ");
                Serial.println(value);
                pinMode(atoi(keys[i]), OUTPUT);
                digitalWrite(atoi(keys[i]), atoi(value));
             }  
           previousMillis = currentMillis;    
         }
        http.end();
      }
  }
  
}
