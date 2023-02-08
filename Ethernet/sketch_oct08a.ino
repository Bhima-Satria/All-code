#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 112);   //ethernet
EthernetClient client;

IPAddress server(192, 168, 1, 111); //computer

unsigned long lastConnectionTime = 0;           // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 10 * 1000; // delay between updates, in milliseconds

int temp1[2];
int temp2[2];
int stat1;
int stat2;
int bt1 = A1;
int bt2 = A2; //PIN berada pada PIN A2 ya mas.

void setup() {
  pinMode(bt1, INPUT);
  pinMode(bt2, INPUT);

  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");

    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1); 
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    Ethernet.begin(mac, ip);
    Serial.print("My IP address: ");
    Serial.println(Ethernet.localIP());
  } else {
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }
  delay(1000);
  
  temp1[0] = digitalRead(bt1);
  temp1[1] = digitalRead(bt1);
  
}

void loop() {
  if (client.available()) {
    char c = client.read();
    
    Serial.write(c);
  }

  temp1[0] = digitalRead(bt1);

  if (temp1[0] != temp1[1]) {
    stat1 = temp1[0];
    temp1[1] = temp1[0];
    httpRequest();
  }
  if (temp2[0] !=temp2[1]){
    stat2 = temp2[0];
    temp2[1] = temp2[0];
    httpRequest();
  }
}

void httpRequest() {
  client.stop();

  if (client.connect(server, 80)) {
    Serial.println("connecting...");

    if (stat1==1) client.println("GET /ethernet1.php?a=1 HTTP/1.1");
    if (stat1==0) client.println("GET /ethernet2.php?b=0 HTTP/1.1");

    client.println("Host: 192.168.1.111");
    client.println("User-Agent: arduino-ethernet");
    client.println("Connection: close");
    client.println();

    lastConnectionTime = millis();
  } else {
    Serial.println("connection failed");
  }
}
