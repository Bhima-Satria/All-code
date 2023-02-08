#include <SPI.h>
#include <SD.h>

File myFile;int suhu=89;
int ctrl_z=26;

void setup() {
  
 Serial.begin(9600);
 Serial1.begin(9600);
 
Serial.println("Initializing...");
  delay(1000);

  Serial1.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  delay(1000);
  Serial1.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  updateSerial();
  delay(1000);
  Serial1.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
  updateSerial();
  delay(1000);
  Serial1.println("AT+CREG?"); //Check whether it has registered in the network
  updateSerial();

   Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  // re-open the file for reading:
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

void loop() {
  updateSerial();
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    Serial1.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(Serial1.available()) 
  {
    Serial.write(Serial1.read());//Forward what Software Serial received to Serial Port
  }
}
