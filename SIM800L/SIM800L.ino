#include <SoftwareSerial.h>

//Create software serial object to communicate with A6
SoftwareSerial mySerial(2, 3); 

unsigned char ctrl_z = 26;
int suhu = 29;

void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  
  //Begin serial communication with Arduino and A6
  mySerial.begin(9600);

  Serial.println("Initializing...");
  delay(1000);
   mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  delay(1000);
  mySerial.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  updateSerial();
  delay(1000);
  mySerial.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
  updateSerial();
  delay(1000);
  mySerial.println("AT+CREG?"); //Check whether it has registered in the network
  updateSerial();
  
mySerial.println("AT+CIPSHUT\r");                                            //RESPONSE= OK
updateSerial();
delay(1000);

mySerial.println("AT+CIPMUX=0\r");                                          //RESPONSE= OK
updateSerial();
delay(2000);

mySerial.println("AT+CGATT=1\r");                                            //RESPONSE= OK
updateSerial();
delay(10000);


mySerial.println("AT+CSTT=\"internet\",\"\",\"\"\r");                   //RESPONSE= OK
updateSerial();
delay(5000);


mySerial.println("AT+CIICR\r");                                                  //RESPONSE= OK
updateSerial();
delay(5000);


mySerial.println("AT+CIFSR\r");                                                 //RESPONSE= Returns an IP
updateSerial();
delay(2000);


mySerial.println("AT+CIPSTART=\"TCP\",\"elektro.um.ac.id\", 80\r");    //RESPONSE= CONNECTED OK
updateSerial();
delay(5000);

mySerial.println("AT+CIPSEND\r");                                //RESPONSE= >
updateSerial();
delay(500);

mySerial.println("POST http://elektro.um.ac.id/research/smartgarden/submit.php?"+String(suhu)+"HTTP/1.1");
updateSerial();
delay(500);

mySerial.println("Host: elektro.um.ac.id");
updateSerial();
delay(1000);

mySerial.write(ctrl_z);
updateSerial();
delay(10000);

mySerial.println("AT+CIPSEND?");                                          //RESPONSE= OK
updateSerial();
delay(1000);

mySerial.println("AT+CIPCLOSE");                                          //RESPONSE= OK
updateSerial();
delay(1000);

  mySerial.println("AT+CIPSHUT");                                            //RESPONSE= OK
  updateSerial();
  delay(1000);
}

void loop()
{
  updateSerial();
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
