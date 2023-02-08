#include <ESP8266WiFi.h>
#include <Servo.h> 
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#define ON HIGH
#define OFF LOW


int relay1 = D0; //pintu
int relay2 = D1;  //kipas
int relay3 = D2; //lampu
int value1 = OFF ;
int value2 = OFF ;
int value3 = OFF;
WiFiServer server(80); 
Servo myservo;


void setup() {
  Serial.begin(115200);
  WiFiManager wifiManager;
  wifiManager.autoConnect("Coba TA");
  
  myservo.attach(D0);
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(relay3,OUTPUT);
  digitalWrite(relay1, ON);
  digitalWrite(relay2, ON);
  digitalWrite(relay3, ON);


 
  server.begin(); //prosedur memulai akses server
  Serial.println("Pemulaian Akses Server");

 }

void loop()  {
  WiFiClient client = server.available(); //cek kondisi jika terhubung dengan client
  if (!client) {
    return;
  }
 
  //menunggu client, data dikirim
  Serial.println("client baru");
  //jika client tidak available
  while(!client.available()) {delay(5);}
  String request = client.readStringUntil('\r');
  Serial.print(request);client.flush();
  
  //penulisan data pada browser dengan alamat diatas
  client.println("HTTP/192.168.1.84 OK");
  client.println("Content-Type: text/html");
  client.println("");
 
  client.println("<!DOCTYPE HTML>");client.println("<html>");
  client.println("<fieldset>");client.println("<font color = red>");
  client.print("Kendali relay via Wifi");
  client.println("</font>");client.println("</fieldset>");
  client.println("<br><br>");
 
  client.print("relay 1 is now: ");
  // Control relay 1
  if(request.indexOf("/relay1=ON")!= -1)
  {myservo.write(180);value1 = ON;}
 
  if(request.indexOf("/relay1=OFF")!= -1)
  {myservo.write(90);value1 = OFF;}
  if(value1==ON){client.print("ON");}
  if(value1==OFF){client.print("OFF");}
    
  client.println("<br><br>");
  client.println("<a href=\"/relay1=ON\"\"><button>relay1 ON </button></a>");
  client.println("<a href=\"/relay1=OFF\"\"><button>relay1 OFF </button></a><br />");  
  client.println("</html>");

  client.print("relay 2 is now: ");
  // Control relay 2
  if(request.indexOf("/relay2=ON")!= -1)
  {digitalWrite(relay2, ON);value2 = ON;}
 
  if(request.indexOf("/relay2=OFF")!= -1)
  {digitalWrite(relay2, OFF);value2 = OFF;}
  if(value2==ON){client.print("ON");}
  if(value2==OFF){client.print("OFF");}
    
  client.println("<br><br>");
  client.println("<a href=\"/relay2=ON\"\"><button>relay2 ON </button></a>");
  client.println("<a href=\"/relay2=OFF\"\"><button>relay2 OFF </button></a><br />");  
  client.println("</html>");

   client.print("relay 3 is now: ");
  // Control relay 3
  if(request.indexOf("/relay3=ON")!= -1)
  {digitalWrite(relay3, ON);value3 = ON;}
 
  if(request.indexOf("/relay3=OFF")!= -1)
  {digitalWrite(relay3, OFF);value3 = OFF;}
  if(value3==ON){client.print("ON");}
  if(value3==OFF){client.print("OFF");}
    
  client.println("<br><br>");
  client.println("<a href=\"/relay3=ON\"\"><button>relay3 ON </button></a>");
  client.println("<a href=\"/relay3=OFF\"\"><button>relay3 OFF </button></a><br />");  
  client.println("</html>");

  client.println("<br><br>");
  client.print("Suhu Saat ini :");
  client.println("90");
  client.println("</html>");
  
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
}
