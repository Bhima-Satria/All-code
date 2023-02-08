#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char *ssid =  "Vinolia I No.10A";     // replace with your wifi ssid and wpa2 key
const char *pass =  "1sampai2puluh";
const char *server = "smartgardend3.000webhostapp.com";
const float  OffSet = 0.54;
float V,P,M ;

WiFiClient client;
HTTPClient http;
 
void setup() 
{
       Serial.begin(115200);
       delay(10);
 
       Serial.println("Connecting to ");
       Serial.println(ssid);
 
 
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
 
}
 
void loop() 
{
  
V = analogRead(A0) * 3.30 / 1024;     //Sensor output voltage
if  (V < 0.54)
{
  V= 0.54;
}
else

P = (V - OffSet) * 400;             //Calculate water pressure
M = P/5.58;
                        
                 if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = "/submit.php?Suhu=";
                             postStr += String(P);
                             postStr +="&Kelembaban=";
                             postStr += String(V);
                             postStr +="&FLC=";
                             postStr += String(M);
                             client.print(String("GET ") + postStr + "HTTP/1.1\n\n" + "Host: " + server + "\n\n" + "Connection: close\r\n\r\n");
                          
                            /* client.print("HTTP/1.1\n");
                             client.print("Host: smartgardend3.000webhostapp.com\n");
                             client.print("Connection: close\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr); */
                             Serial.println("submited");

                        }
          client.stop();
 
          Serial.println("Waiting...");
  delay(10000);
}
