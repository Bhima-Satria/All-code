#include <ESP8266WiFi.h>
#include <ThingsBoard.h>

#define WIFI_AP "Workshop_Batujajar"
#define WIFI_PASSWORD "Workshop2020"

#define TOKEN "node_1_token"

char thingsboardServer[] = "thingsbox-mqtt-uat.zebrax.id";

WiFiClient wifiClient;

ThingsBoard tb(wifiClient);

int status = WL_IDLE_STATUS;
unsigned long lastSend;

void setup()
{
  Serial.begin(115200);
  delay(10);
  InitWiFi();
  lastSend =0;
}

void loop()
{
  if ( !tb.connected() ) {
    reconnect();
  }

  if ( millis() - lastSend > 600000 ) { // Update and send only after 1 seconds
    getAndSendTemperatureAndHumidityData();
    lastSend = millis();
  }

  tb.loop();
}

void getAndSendTemperatureAndHumidityData()
{
  Serial.println("Collecting temperature data.");

//  float Kelembapan = random(67,70);
//  float Suhu = random(23,30);
//  float Soil = random(5,10);
char Suhu[] = "{\"Suhu\":[48.756080,2.302038]}";
char Kelembapan[] = "{\"Kelembapan\":[48.756080,2.302038]}";
char Soil[] = "{\"Soil\":[48.756080,2.302038]}";
      
  Serial.println("Sending data to ThingsBoard:");
  Serial.print("Humidity: ");
  Serial.print(Kelembapan);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(Suhu);
  Serial.print(" *C\t");
  Serial.print("Soil: ");
  Serial.print(Soil);
  Serial.println(" %");

  tb.sendTelemetryFloat("Suhu", Suhu[]);
  tb.sendTelemetryFloat("Kelembapan", Kelembapan[]);
  tb.sendTelemetryFloat("Soil", Soil[]);
}

void InitWiFi()
{
  Serial.println("Connecting to AP ...");
  // attempt to connect to WiFi network

  WiFi.begin(WIFI_AP, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to AP");
}


void reconnect() {
  // Loop until we're reconnected
  while (!tb.connected()) {
    status = WiFi.status();
    if ( status != WL_CONNECTED) {
      WiFi.begin(WIFI_AP, WIFI_PASSWORD);
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }
      Serial.println("Connected to AP");
    }
    Serial.print("Connecting to ThingsBoard node ...");
    if ( tb.connect(thingsboardServer, TOKEN) ) {
      Serial.println( "[DONE]" );
    } else {
      Serial.print( "[FAILED]" );
      Serial.println( " : retrying in 5 seconds]" );
      // Wait 5 seconds before retrying
      delay( 5000 );
    }
  }
}
