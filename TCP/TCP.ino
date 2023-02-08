#include <Ethernet.h>
#include <SPI.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,100,6);
EthernetServer server(80);
char arrayRead;

void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.begin(9600);
   while (!Serial) {
    ; 
  }
}
void loop() {
    EthernetClient client = server.available();
      if (client.available() > 0) 
      {
        arrayRead = client.read();
            Serial.print(arrayRead);             
      }
    if (!(client.connected())) 
    {
      client.stop();
    }
  }
