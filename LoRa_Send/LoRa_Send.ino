//Libraries for LoRa
#include <SPI.h>
#include <LoRa.h>

//Libraries for OLED Display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//PZEM
#include <PZEM004Tv30.h>
#include <HardwareSerial.h>

//define the pins used by the LoRa transceiver module
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26

//433E6 for Asia
//866E6 for Europe
//915E6 for North America
#define BAND 915E6

//OLED pins
#define OLED_SDA 4
#define OLED_SCL 15
#define OLED_RST 16
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

//packet counter
int counter = 0;

//Led PIN
const int Led_a = 2;
const int Led_b = 4;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

//PZEM
#define RXD2 13
#define TXD2 21

PZEM004Tv30 pzem(&Serial2);

void setup() {

  //reset OLED display via software
  pinMode(OLED_RST, OUTPUT);
  pinMode(Led_a, OUTPUT);
  pinMode(Led_b, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(20);
  digitalWrite(OLED_RST, HIGH);
  digitalWrite(Led_b, HIGH);
  digitalWrite(Led_a, HIGH);

  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  //initialize OLED
  Wire.begin(OLED_SDA, OLED_SCL);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("LORA SENDER ");
  display.display();

  //initialize Serial Monitor
  Serial.begin(115200);

  Serial.println("LoRa Sender Test");

  //SPI LoRa pins
  SPI.begin(SCK, MISO, MOSI, SS);
  //setup LoRa transceiver module
  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa Initializing OK!");
  display.setCursor(0, 10);
  display.print("LoRa Initializing OK!");
  display.display();
  delay(2000);
  LoRa.setTxPower(20);
}

void loop() {
  LoRa_Send();
}


void LoRa_Send() {
  float current;
  String  indikator;
  char kirim[37];

  current  = pzem.current();

  Serial.print("Sending packet: ");
  Serial.println(counter);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("LORA SENDER");
  display.setCursor(0, 20);
  display.setTextSize(1);
  display.print("LoRa packet sent.");
  display.setCursor(0, 30);
  display.print("Counter:");
  display.setCursor(50, 30);
  display.print(counter);
  if (current != NAN) {
    display.setCursor(0, 40);
    display.print("Arus : ");
    display.setCursor(40, 40);
    display.print(current);
  } else {
    display.setCursor(0, 40);
    display.print("Arus : ");
    display.setCursor(40, 40);
    display.print("Error");
  }

  if (current <= 0.00) {
    indikator = "+OFF";
    display.setCursor(0, 50);
    display.print("Pump : ");
    display.setCursor(40, 50);
    display.print("OFF");
  } 
  else {
    indikator = "+ON";
    display.setCursor(0, 50);
    display.print("Pump : ");
    display.setCursor(40, 50);
    display.print("ON");
  }

  
  display.display();

  counter++;

  String arus, hitung;
  char LoRa_arus[16];
  char LoRa_htng[16];
  char LoRa_indk[16];

  arus = String("+") + String(current);
  hitung = String(counter);

  arus.toCharArray(LoRa_arus, 16);
  hitung.toCharArray(LoRa_htng, 16);
  indikator.toCharArray(LoRa_indk, 16);

  strcpy(kirim, LoRa_htng);
  strcpy(kirim + strlen(LoRa_htng), LoRa_indk);
  strcpy(kirim + strlen(LoRa_htng) + strlen(LoRa_indk), LoRa_arus);

  //Send LoRa packet to receiver
  LoRa.beginPacket();
  LoRa.print(kirim);
  digitalWrite(Led_a, LOW);
  delay(1000);
  digitalWrite(Led_a, HIGH);
  LoRa.endPacket();
  delay(500);

  if (counter >= 999){
    counter = 0;
  }
}
