#include <SoftwareSerial.h>
#define DEBUG true

int a = analogRead(A0);
int b;

void setup() {
// put your setup code here, to run once:
Serial.begin(115200);
}
void loop() {
// put your main code here, to run repeatedly:

}
void set_wifi() {
Serial.print("Restart Module...\n");
sendCommand("AT+RST\r\n", 2000, DEBUG); // reset module
Serial.print("Set Mode Wifi\n");
sendCommand("AT+CWMODE=1\r\n", 1000, DEBUG); // client
Serial.print("Connect to access point...\n");
sendCommand("AT+CWJAP=\"Research Team\",\"12345678\"\r\n", 5000, DEBUG);
Serial.print("Check IP Address...\n");
sendCommand("AT+CIFSR\r\n", 5000, DEBUG); // get ip address
}
String sendCommand(String command, const int timeout, boolean debug) {
String response = "";
ser.print(command); // send the read character to the esp8266
long int time = millis();
while ( (time + timeout) > millis()) {
while (ser.available()) {
// The esp has data so display its output to the serial window
char c = ser.read(); // read the next character.
response += c;
}
}
if (debug) {
Serial.print(response);
}
return response;
}
void kirim(){
String cmd = "AT+CIPSTART=\"TCP\",\"";
cmd += "192.168.1.77";
cmd += "\",80\r\n";
sendCommand(cmd, 1000, DEBUG);
return;
}
delay(3000);
String cmd2 = "GET /Project_air/Konten.php?"; // Link ke skrip PHP
cmd2 += "&adc=";
cmd2 += String(b);
cmd2 += " HTTP/1.1\r\n";
cmd2 += "Host: alamatserver\r\n\r\n\r\n";
//cmd2 += " HTTP/1.0\r\n\r\n";
String pjg = "AT+CIPSEND=";
pjg += cmd2.length();
pjg += "\r\n\r\n";
sendCommand(pjg, 3000, DEBUG);
delay(100);
sendCommand(cmd2, 3000, DEBUG);
delay(100);
}
void adc(){
b = analogRead(a);
}
