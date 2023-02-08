#include <ESP8266WiFi.h>
#define Led LED_BUILTIN


const char* ssid = "warriornux.com";       // Nama SSID AP/Hotspot
const char* password = "1234567890";       // Password Wifi

IPAddress host(192,168,4,1);       // IP Server


int sensorPin = A0; 
int sensorValue;  
int limit = 300; 

void setup() {
  Serial.begin(115200);
  pinMode(Led, OUTPUT);
  delay(10);

// Connect to WiFi network ------------------------------------------------
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

// Mengatur WiFi ----------------------------------------------------------
  WiFi.mode(WIFI_STA);                      // Mode Station
  WiFi.begin(ssid, password);               // Mencocokan SSID dan Password
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

// Print status Connect ---------------------------------------------------
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

int value = 0;

void loop() {
  delay(5000);
  ++value;

  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
   sensorValue = random(0,500); 
   Serial.println("Analog Value : ");
   Serial.println(sensorValue);
   
   if (sensorValue<limit) {
   digitalWrite(Led, HIGH); 
   }
   else {
   digitalWrite(Led, LOW); 
   }

  // We now create a URI for the request
  String url = String(sensorValue);
  
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
}
