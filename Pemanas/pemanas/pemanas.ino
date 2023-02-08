#include <arduino.h>
#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>
#include <Servo.h>;
#include <SPI.h>
#include <MFRC522.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define SS_PIN 10
#define RST_PIN 9
#define relay A0
#define relay1 A1
#define relay2 A2
#define ONE_WIRE_BUS 2

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

MFRC522::MIFARE_Key key;

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);
// Init array that will store new NUID
byte nuidPICC[4];

const int buttonPin = 5;
const int buttonPin1 = 6;
const int buttonPin2 = 7;
int counter = 0;
int DS18S20_Pin = 2;

int buttonState = 0;
int buttonState1 = 0;
int buttonState2 = 0;


Servo Servo1;
Servo Servo2;
OneWire ds(DS18S20_Pin);

void setup() {
  Servo1.attach(3);
  Servo2.attach(4);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  
  pinMode(relay,OUTPUT);
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  digitalWrite(relay,HIGH);
  digitalWrite(relay1,HIGH);
  digitalWrite(relay2,HIGH);
  
  
  Serial.begin(9600);   // Initiate a serial communication

  sensors.begin();
  
  SPI.begin();      // Initiate  SPI bus
  rfid.PCD_Init(); // Init MFRC522
  Serial.println("Scan Kartu Anda");
}

void loop() {
  
  buttonState = digitalRead(buttonPin);
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  
  int authorized_flag = 0;
  // Look for new cards
  if ( ! rfid.PICC_IsNewCardPresent()) {
    delay(50);
    return;
  }
  // Select one of the cards
  if ( ! rfid.PICC_ReadCardSerial()) {
    delay(50);
    return;
  }

  // Shows the card ID on the serial console
  String content = "";
  for (byte i = 0; i < rfid.uid.size; i++)
  {
    content.concat(String(rfid.uid.uidByte[i] < 0x10 ? "0" : ""));
    content.concat(String(rfid.uid.uidByte[i], DEC));
  }
  
  content.toUpperCase();
  //Serial.println("Cart read:"+content);
  //delay(1000);
  
 String data = "073218199";
 if (data == content) {
  // Tambah kondisi if else LDR 
  sensors.requestTemperatures(); 
  
  float tempC = sensors.getTempCByIndex(0);
  Serial.println(tempC);
  
    if (tempC < 40) {
    digitalWrite(relay1, LOW);
    Servo1.write(90);
    Servo2.write(90);
  } 
  else if (tempC > 40) {
    digitalWrite(relay1, HIGH);
    if (buttonState == LOW) {
        Serial.println("Servo aktif");
        Servo1.write(180);
        delay(1000);
        Servo1.write(90);
        delay(100);
        Servo2.write(180);
        delay(3000);
        Servo2.write(90);
        delay(100);
        digitalWrite(relay, LOW);
        delay(2000);
        digitalWrite(relay, HIGH);
        delay(100);
        Serial.println("Servo mati");
        digitalWrite(relay2, LOW);
        delay(2000);
        digitalWrite(relay2, HIGH);
        delay(100);
      }

      if (buttonState1 == LOW) {
        Serial.println("Servo aktif");
        Servo1.write(180);
        delay(2000);
        Servo1.write(90);
        delay(100);
        Servo2.write(180);
        delay(3000);
        Servo2.write(90);
        delay(100);
        digitalWrite(relay, LOW);
        delay(2000);
        digitalWrite(relay, HIGH);
        delay(100);
        Serial.println("Servo mati");
        digitalWrite(relay2, LOW);
        delay(2000);
        digitalWrite(relay2, HIGH);
        delay(100);
      }

      if (buttonState2 == LOW) {
        Serial.println("Servo aktif");
        Servo1.write(180);
        delay(3000);
        Servo1.write(90);
        delay(100);
        Servo2.write(180);
        delay(3000);
        Servo2.write(90);
        delay(100);
        digitalWrite(relay, LOW);
        delay(2000);
        digitalWrite(relay, HIGH);
        delay(100);
        Serial.println("Servo mati");
        digitalWrite(relay2, LOW);
        delay(2000);
        digitalWrite(relay2, HIGH);
        delay(100);
      }
     } 
  
  }
}


void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

/*void suhu(){
  sensors.requestTemperatures(); 
  
  float tempC = sensors.getTempCByIndex(0);

    Serial.println(tempC);
    if (tempC < 30) {
    digitalWrite(relay1, HIGH);
  } 
  else if (tempC > 40) {
    digitalWrite(relay1, LOW);
  } 
 
}*/
