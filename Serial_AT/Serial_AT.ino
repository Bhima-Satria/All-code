#include <SoftwareSerial.h>

char c = ' ';

SoftwareSerial Serial1(7,6);

void setup() 
{
  
    // start th serial communication with the host computer
    Serial.begin(9600);
    while(!Serial);
    Serial.println("Arduino with SIM800L is ready");
 
    // start communication with the SIM800L in 9600
    Serial1.begin(9600);  
    Serial.println("SIM800L started at 9600");
    delay(1000);
    Serial.println("Setup Complete! SIM800L is Ready!");
}
 
void loop()
{
 
     // Keep reading from SIM800 and send to Arduino Serial Monitor
    if (Serial1.available())
    { c = Serial1.read();
      Serial.write(c);}
 
    // Keep reading from Arduino Serial Monitor and send to SIM800L
    if (Serial.available())
    { c = Serial.read();
      Serial1.write(c);  
       }

}
