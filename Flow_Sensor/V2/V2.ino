#include <EEPROM.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <Adafruit_SSD1306.h>
//#include <TimeLib.h>

#define OLED_RESET 4
#define but_on 12
Adafruit_SSD1306 display(OLED_RESET);



// byte indikator = 13;
byte sensorInt = 0; 
byte flowsensor = 2; //sensor pin
float konstanta = 4.5; //konstanta flow meter
volatile byte pulseCount;
float debit;
unsigned int flowmlt;
unsigned long totalmlt;
unsigned long previustimer = 0;
unsigned long interval_detik = 604800; // 7 hari dalam detik 

int Simpan_Debit = 1;
int lastDebit;

unsigned long oldTime;

//SIM 800L
String apn = "internet";											  //APN
String apn_u = "";													  //APN-Username
String apn_p = "";													  //APN-Password
String url = "http://siprida.databumi.id/etax/Api/getPorporasi.php?"; //URL for HTTP-POST-REQUEST

//void printkurangdarinol(int data);

SoftwareSerial mySerial(10, 11); //RX TX

void setup()
{
	Serial.begin(9600);
	mySerial.begin(9600);

 //Automatic Sleep Mode
  mySerial.println("AT");
  runs1();
  mySerial.println("AT+CSCLK=2");
  runs1();

//	setTime(5,57,40,3,2,20); //(Jam,Menit,Detik,Tanggal,Bulan,Tahun)

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
	//EEPROM.write(Simpan_Debit, 0);
	lastDebit = EEPROM.read(Simpan_Debit);

	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	display.clearDisplay();
}

void loop()
{
	unsigned long currenttimer = millis() / 1000;
	if ((unsigned long)(currenttimer - previustimer) >= interval_detik)
	{
		display.clearDisplay();
		display.setTextSize(1);
		display.setTextColor(WHITE);
		display.setCursor(0, 5);
		display.print("Kirim Data...");
		display.display();
		delay(1000);
		gsm_sendhttp();
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
			Serial.print(EEPROM.read(Simpan_Debit));
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

void gsm_sendhttp()
{

	int Kirimdebit = EEPROM.read(Simpan_Debit);

	delay(5000);
	mySerial.println("AT");
  runs1(); //Print GSM Status an the Serial Output;
  delay(700);
  mySerial.println("AT+CSCLK=0");
  runs1();
	delay(2000);
	mySerial.println("AT+SAPBR=3,1,Contype,GPRS");
	runs1();
	delay(100);
	mySerial.println("AT+SAPBR=3,1,APN," + apn);
	runs1();
	delay(100);
	//  mySerial.println("AT+SAPBR=3,1,USER," + apn_u); //Comment out, if you need username
	runs1();
	delay(100);
	//  mySerial.println("AT+SAPBR=3,1,PWD," + apn_p); //Comment out, if you need password
	runs1();
	delay(100);
	mySerial.println("AT+SAPBR =1,1");
	runs1();
	delay(100);
	mySerial.println("AT+SAPBR=2,1");
	runs1();
	delay(2000);
	mySerial.println("AT+HTTPINIT");
	runs1();
	delay(100);
	mySerial.println("AT+HTTPPARA=CID,1");
	runs1();
	delay(100);
	mySerial.println("AT+HTTPPARA=URL," + url + "Debit=" + Kirimdebit);
	runs1();
	delay(100);
	mySerial.println("AT+HTTPPARA=CONTENT,application/x-www-form-urlencoded");
	runs1();
	delay(100);
	mySerial.println("AT+HTTPDATA=192,10000");
	runs1();
	delay(10000);
	mySerial.println("AT+HTTPACTION=1");
	runs1();
	delay(5000);
	mySerial.println("AT+HTTPREAD");
	runs1();
	delay(100);
	mySerial.println("AT+HTTPTERM");
	runs1();
  delay(100);
  mySerial.println("AT+CSCLK=2");
  runs1();
}

void runs1()
{
	while (mySerial.available())
	{
		Serial.write(mySerial.read());
	}
}

//void Jam()
//{
 
//	printkurangdarinol(hour());
//	display.print(":");
//	printkurangdarinol(minute());
//	display.print(":");
//	printkurangdarinol(second());

//}

//void printkurangdarinol(int data)
//{
//	if (data >= 0 && data < 10)
//	{
//		display.print('0');
//	}
//	display.print(data);
//}
