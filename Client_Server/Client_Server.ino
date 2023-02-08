#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

int a=192;
int b=168;
int c=1;
int d=2;

int id;
int tgl;
int jam;
int Rp;
int Pj;

char data;
String set;

IPAddress ip(a,b,c,d);
EthernetServer server(80);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Setting Up TCP");

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

  // start the server
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();

      if (client.available()>0) {
        data = client.read();
        set+=data;
        Serial.write(data);
        delay(1000);
      } 
        if (set=="0"){
         server.write("E-Stamp");
         set="";
        }
        else if (set=="1"){
          server.write("id_Pajak");
          set="";
        }
        else if (set=="2"){
          server.write("id_black box");
          set="";
        }
        else if (set=="3"){
          server.write("Set_Jam");
          set="";
        }
        else if (set=="4"){
          server.write("set_IP");
          set="";
        }
        else {set="";}
  
}
