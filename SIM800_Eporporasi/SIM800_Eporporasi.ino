#include <SD.h>
#include <SPI.h>
#include <Ethernet.h>

//Ethernet 
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 137, 177);
IPAddress server(192,168,100,43);
EthernetClient client;
char c;

//SIM 800L
String apn = "internet";                       //APN
String apn_u = "";                     //APN-Username
String apn_p = "";                     //APN-Password
String url = "elektro.um.ac.id/research/smartgarden/submit.php?";  //URL for HTTP-POST-REQUEST
int data1;   //String for the first Paramter (e.g. Sensor1)
int data2;   //String for the second Paramter (e.g. Sensor2)

//SD Card
File myFile;




void setup() {
  //Start Ethernet
  Ethernet.begin(mac, ip);
  
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.println("Initializing SD card...");
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
  
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  while (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
    delay(500);
  }
  delay(1000);
  Serial.println("connecting...");
    if (client.connect(server, 10002)) {
    Serial.println("connected");
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
  client.print("Reach the Server...");
  delay(1000);
  
  //SIM800L
  Serial1.begin(9600);
  delay(10000);
  Serial.println("SIM800 Start....");

}

void loop() { // run over and over

  if (client.available()) {
      c = client.read();
    Serial.print(c);
  
  data1 = c ;
  data2 = c ;
  
  gsm_sendhttp(); //Start the GSM-Modul and start the transmisson
  SDcard();
  delay(60000); //Wait one min
  }
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    while (true) {
      delay(1);
    }
  }
}


void gsm_sendhttp() {



  Serial1.println("AT");
  runsl();//Print GSM Status an the Serial Output;
  delay(4000);
  Serial1.println("AT+SAPBR=3,1,Contype,GPRS");
  runsl();
  delay(100);
  Serial1.println("AT+SAPBR=3,1,APN," + apn);
  runsl();
  delay(100);
  //  Serial1.println("AT+SAPBR=3,1,USER," + apn_u); //Comment out, if you need username
  runsl();
  delay(100);
  //  Serial1.println("AT+SAPBR=3,1,PWD," + apn_p); //Comment out, if you need password
  runsl();
  delay(100);
  Serial1.println("AT+SAPBR =1,1");
  runsl();
  delay(100);
  Serial1.println("AT+SAPBR=2,1");
  runsl();
  delay(2000);
  Serial1.println("AT+HTTPINIT");
  runsl();
  delay(100);
  Serial1.println("AT+HTTPPARA=CID,1");
  runsl();
  delay(100);
  Serial1.println("AT+HTTPPARA=URL," + url + "Suhu=" + String(data1) + "&Kelembaban=" + String(data2));
  runsl();
  delay(100);
  Serial1.println("AT+HTTPPARA=CONTENT,application/x-www-form-urlencoded");
  runsl();
  delay(100);
  Serial1.println("AT+HTTPDATA=192,10000");
  runsl();
  delay(100);
  //  Serial1.println("Suhu=" + data1);
  runsl();
  delay(10000);
  Serial1.println("AT+HTTPACTION=1");
  runsl();
  delay(5000);
  Serial1.println("AT+HTTPREAD");
  runsl();
  delay(100);
  Serial1.println("AT+HTTPTERM");
  runsl();
}

//Print GSM Status
void runsl() {
  while (Serial1.available()) {
    Serial.write(Serial1.read());
  }

}



// Write SD Card

void SDcard (){
   myFile = SD.open("test.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("Suhu="+String(data1)+";Kelembaban="+String(data2));
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  Serial.println("Open SD Card....");
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

}
