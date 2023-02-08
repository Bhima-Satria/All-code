#include <EEPROM.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define OLED_RESET 4
#define but_on 3
Adafruit_SSD1306 display(OLED_RESET);



byte sensorInt = 0; 
byte flowsensor = 2; //sensor pin
float konstanta = 4.5; //konstanta flow meter
volatile byte pulseCount;
float debit;
unsigned int flowmlt;
unsigned long totalmlt;
unsigned long previustimer = 0;
//unsigned long interval_detik = 604800; // 7 hari dalam detik 
unsigned long interval_detik = 60;

int Simpan_Debit = 1;
int lastDebit;
unsigned long oldTime;

RF24 radio(9, 10); // CE, CSN

byte address[] = "Node1";
char prefix [] = ";";
char prefix2[] = "+";

void setup()
{

//  Radio
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  
//  Flow Metter
	pinMode(but_on, INPUT_PULLUP);
	pinMode(flowsensor, INPUT);
	digitalWrite(flowsensor, HIGH);
	pulseCount = 0;
	debit = 0.0;
	flowmlt = 0;
	totalmlt = 0;
	oldTime = 0;
	attachInterrupt(sensorInt, pulseCounter, FALLING);
	// EEPROM.write(Simpan_Debit, 0);
	lastDebit = EEPROM.read(Simpan_Debit);

	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	display.clearDisplay();
}

void loop()
{
	unsigned long currenttimer = millis() / 1000;
	if ((unsigned long)(currenttimer - previustimer) >= interval_detik)
	{

    int datadebit=EEPROM.read(Simpan_Debit);

		
		display.clearDisplay();
		display.setTextSize(1);
    if (digitalRead(but_on) == LOW){
      display.setTextColor(WHITE);
     } 
     else {
      display.setTextColor(BLACK);
     }
		display.setCursor(0, 5);
		display.print("Kirim Data... \n");
    display.setCursor(0, 15);
    display.print("Total Debit : ");
    display.print(datadebit);
		display.display();

//Kirim Data
  String str,str1;
  str=String(datadebit);
  str1=String(currenttimer);
  char datasend[6];
  char waktu_kirim[15];
  str.toCharArray(datasend,6);
  str1.toCharArray(waktu_kirim,32);
  
  char kirim [64];
  strcpy(kirim, datasend);
  strcpy(kirim + strlen(datasend), prefix);
  strcpy(kirim + strlen(datasend)+strlen(prefix), address);
  strcpy(kirim + strlen(datasend)+strlen(prefix)+strlen(address), prefix);
  strcpy(kirim + strlen(datasend)+strlen(prefix)+strlen(address)+strlen(prefix), waktu_kirim);
  strcpy(kirim + strlen(datasend)+strlen(prefix)+strlen(address)+strlen(prefix)+strlen(waktu_kirim), prefix2);
  radio.write(&kirim, sizeof(kirim));
  
	previustimer = currenttimer;
  
	}
 
	else if ((unsigned long)(currenttimer - previustimer) < interval_detik)
	{
		if ((millis() - oldTime) > 1000)
		{
			detachInterrupt(sensorInt);
			debit = ((1000.0 / (millis() - oldTime)) * pulseCount) / konstanta;
			oldTime = millis();
			flowmlt = (debit / 60) * 1000;
			totalmlt += flowmlt;
			int kubik = (totalmlt / 1000);
			int Debitbaru = lastDebit + kubik;
			unsigned int frac;
			display.clearDisplay();
			display.setTextSize(1);
     
     if (digitalRead(but_on) == LOW){
			display.setTextColor(WHITE);
     } 
     else {
      display.setTextColor(BLACK);
     }
     
			display.setCursor(0, 2);
			display.print("Debit  : ");
			display.print(int(debit));
			display.print("L/min \n");
			display.setCursor(0, 12);
			EEPROM.write(Simpan_Debit, Debitbaru);
			display.print("Total  : ");
			display.print(EEPROM.read(Simpan_Debit));
			display.print("m3 \n");
			display.setCursor(0, 22);
			display.print("Timer  : ");
			display.print(currenttimer);
			pulseCount = 0;
			attachInterrupt(sensorInt, pulseCounter, FALLING);
			display.display();
		}
	}
}
void pulseCounter()
{
	// Increment the pulse counter
	pulseCount++;
}
