/*************************************
 * Program : Project 2: Kontrol 2 LED
 * Input : -
 * Output : LED1 + LED 2
 * Iot Starter Kit Inkubatek
 * www.tokotronik.com
 * ***********************************/
#include <ESP8266WiFi.h> 
const char* ssid = "FirnasAbe";
const char* password = "podowingi";
#define LED1 D5
#define LED2 D6 

WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
   
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid); 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  server.begin();
  Serial.println("Server started");
 
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/"); 
}
 
void loop() { 
  WiFiClient client = server.available();
  if (!client) {
    return;
  } 
  
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  } 
 
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  if (request.indexOf("/led1on") > 0)  {
    digitalWrite(LED1, HIGH);
   
  }
  if (request.indexOf("/led1off") >0)  {
    digitalWrite(LED1, LOW);   
  }
   if (request.indexOf("/led2on") > 0)  {
    digitalWrite(LED2, HIGH);   
  }
  if (request.indexOf("/led2off") >0)  {
    digitalWrite(LED2, LOW);   
  }
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); 
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
  client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
  client.println("</head>");
  client.println("<body bgcolor = \"#f7e6ec\">"); 
  client.println("<hr/><hr>");
  client.println("<h4><center> IoT Starter Kit : Kontrol 2 LED  </center></h4>");
  client.println("<hr/><hr>");
  client.println("<br><br>");
  client.println("<br><br>");
  client.println("<center>");
  client.println("LED 1");
  client.println("<a href=\"/led1on\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/led1off\"\"><button>Turn Off </button></a><br />");  
  client.println("</center>");   
  client.println("<br><br>");
  client.println("<center>");
  client.println("LED 2");
  client.println("<a href=\"/led2on\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/led2off\"\"><button>Turn Off </button></a><br />");  
  client.println("</center>"); 
  client.println("<br><br>");
  client.println("<center>"); 
  client.println("<table border=\"5\">");
  client.println("<tr>");
  //=====================
  if (digitalRead(LED1))
         { 
           client.print("<td>LED 1 = ON</td>");        
         }
  else
          {
            client.print("<td>LED 1 = OFF</td>");
          }     
  client.println("<br />");
  //======================           
  if (digitalRead(LED2))
          { 
           client.print("<td>LED 2 = ON</td>");
          }
  else
          {
            client.print("<td>LED 2 = OFF</td>");
          }
  client.println("</tr>");
  //=======================
  client.println("<tr>"); 
  client.println("</table>");
  client.println("</center>");
  client.println("</html>"); 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println(""); 
}
