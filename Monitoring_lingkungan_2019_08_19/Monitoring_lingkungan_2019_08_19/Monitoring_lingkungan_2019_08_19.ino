//Program monitoring pada TPA
//======================================

//Header program
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <Wire.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>
#include <DS3231.h>
#include <SD.h>
#include <Adafruit_INA219.h> //Header Power 
#include "DHT.h" //Header Humidity
#include "MQ135.h" //Header CO2
char g = '>';

//Definisi refresh
#define led1 2
#define led2 3
#define led3 4
#define led4 5

////Definisi untuk LCD 20x4
//#define I2C_ADDR 0x27
//#define Rs_pin  0
//#define Rw_pin  1
//#define En_pin  2
//#define BACKLIGHT_PIN 3
//#define D4_pin  4
//#define D5_pin  5
//#define D6_pin  6
//#define D7_pin  7

//Definisi untuk keypad
#define atas 34
#define bawah 42
#define kiri 32
#define kanan 40
#define ok 36
#define back 38

//Definisi indiktor kirim
#define ledftp 8
#define ledrt 9

//Definisi Relay
#define relay1 18
#define relay2 19

//Definisi untuk GSM
#define DEBUG true
String response = "";

//Definisi PIN DHT
#define DHTPIN 46
#define DHTTYPE DHT11

//Definisi Sensor Gas
#define co2_input A12
#define ch4_input A13
#define co_input A15

//Definisi Sensor arah angin dan kecepatan angin
#define wdr_input A9
#define wv_input A11

//Pengaturan GPS
TinyGPSPlus gps;
double Lat;
double Lon;

//Pengaturan pada LCD
LiquidCrystal_I2C lcd(0x27,20,4);

//Pengaturan pada GSM
SoftwareSerial ser(10, 11);
char* kirim = "log.txt";

//Pengaturan RTC3231
DS3231 rtc(SDA, SCL);

//Pengaturan atumatic Reset
int resetcond = 0; //Kondisi untuk reset
int error;
int errorcond;
int coba;
int kondisi = 0;
int kirimftp = 0;

//Pengaturan pada menu
int Data[3];
float dpl, dpl1, dpl2;
int tombol = 1;
int kolom = 1;
int nilai_tps = 1;
bool ganti_nilai_tpa = false;
int nilai_tpa[3] = {0, 0, 0};

//Pengaturan untuk SD
//======================================================
const int SS_SD = 53;
File dataFile;
float suhuin = 0;

//Pengaturan Humidity
DHT dht(DHTPIN, DHTTYPE);

//Pengaturan CO2
MQ135 gasSensor = MQ135(A12);

//Pengaturan Power
Adafruit_INA219 ina219;
uint32_t currentFrequency;
float Power = 0;
float shuntvoltage = 0;
float busvoltage = 0;
float Current = 0;
float Voltage = 0;
float Energy = 0;

//Variabel perhitungan waktu
//====================================================
int count_time;
int count_det;
int count_men;
Time t; //Variabel waktu
int tahun, bulan, tanggal, jam, menit, detik;

//Variabel untuk menyimpan nilai tiap 10 detik
//====================================================
float tempr = 0;
int humr = 0;
float temp_det[6];
//float power_det[6];
float ch4_det[6];
float co_det[6];
float co2_det[6];
int hum_det[6];
int wdr_det[6];
float vel_det[6];
//Variabel untuk menyimpan nilai tiap menit
float temp_men[15];
//float power_men[15];
float ch4_men[15];
float co_men[15];
float co2_men[15];
int hum_men[15];
int wdr_men[15];
float vel_men[15];
//===================================================

byte panah [8] =
{
  0b00000,
  0b00100,
  0b00010,
  0b11111,
  0b00010,
  0b00100,
  0b00000,
  0b00000
};

byte verticalLine[8] =
{
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100
};

byte char2[8] =
{
  B00000,
  B00000,
  B00000,
  B11100,
  B00100,
  B00100,
  B00100,
  B00100
};

byte char1[8] =
{
  0b00000,
  0b00000,
  0b00000,
  0b00111,
  0b00100,
  0b00100,
  0b00100,
  0b00100
};

byte char3[8] =
{
  0b00100,
  0b00100,
  0b00100,
  0b00111,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

byte char4[8] =
{
  0b00100,
  0b00100,
  0b00100,
  0b11100,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

//=================================================================================
//                                      SETUP
//=================================================================================
void setup()
{
  //Setup Komunikasi Serial
  Serial.begin(9600);

  //Setup GPS Modul
  Serial2.begin(9600);

  //Setup GSM modul
  //ser.begin(4800);
  //set_gsm();

//  Setup LCD 20x4
//  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
//  lcd.setBacklight();
  lcd.begin();
  lcd.createChar(0, panah);
  lcd.print(">");

  //Output Relay/Pendingin
  pinMode (relay1, OUTPUT);
  pinMode (relay2, OUTPUT);

  //Pin mode Sensor Gas
  pinMode(co2_input, INPUT);
  pinMode(ch4_input, INPUT);
  pinMode(co_input, INPUT);

  //Pinmode Sensor Kecepatan dan Arah Angin
  pinMode(wdr_input, INPUT);
  pinMode(wv_input, INPUT);

  //Setup SD shield
  pinMode (SS_SD, OUTPUT);  
  if (!SD.begin(SS_SD))
  {
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("Card initialized.");
  delay(1000);

  Serial.println("Running....");

  //Setup RTC 3231
  rtc.begin();
  //rtc.setDOW(TUESDAY);
  //rtc.setTime(13,06,0);
  rtc.setDate(24,8,2019);

  //Setup Humidity
  dht.begin();

  //Setup Powermeter
  ina219.begin();

  
    //Mengecek file yang tersimpan
//    if (SD.exists("log.txt")) {
//      Serial.println("log.txt sudah ada");
//      kirim_ftp();
//      SD.remove("log.txt");
//    }
//    else {
//      Serial.println("log.txt belum ada");
//    }
  
}

void loop()
{
 t = rtc.getTime();
 String Tanggal= rtc.getDateStr();
 String Jam = rtc.getTimeStr();
  // rstactive();//Fungsi reset otomatis
  createCustomCharacters();
  printFrame();
  lcd.setCursor(5, 1);
  lcd.print(Tanggal);
  lcd.setCursor(6, 2);
  lcd.print(Jam);

//  Serial.print("suhu: ");
//  Serial.println(tempread());
//  Serial.print("Kelembaban: ");
//  Serial.println(humread());
  /*
    Serial.print("Tegangan: ");
    Serial.println(vread());
    Serial.print("CO : ");
    Serial.println(coread());
    Serial.print("CH4: ");
    Serial.println(ch4read());
    Serial.print("CO2: ");
    Serial.println(co2read());
    /*
    String detik,menit;
    Serial.print("Waktu: ");
    Serial.print(tm.Hour);
    Serial.print(":");
    if(tm.Minute<10)
    {
    menit = "0"+String(tm.Minute);
    Serial.print(menit);
    }else
    {
    Serial.print(tm.Minute);
    }
    Serial.print(":");
    if(tm.Second<10)
    {
    detik = "0"+String(tm.Second);
    Serial.println(detik);
    }else
    {
    Serial.println(tm.Second);
    }
    //Serial.print(":");
    //Serial.print(tm.Minute);
    //Serial.print(":");
    //Serial.println(tm.Second);
  */
  //Serial.print("Wind Velocity");
  //Serial.println(speedwind);
  //Serial.print("Wind Direction");
  //Serial.println(wdrread());
  //Serial.println(wdrconv());
  read_data();
  if (digitalRead(ok) == LOW)
  {
    delay(10);
    menu();
  }
  refresh();
}

void read_data()
{
  tempr = tempread(); //Temperature
  gpsread();
  daya();
  Serial.print(count_time);
  count_time++;
  if (count_time == 20)
  {
    temp_det[count_det] = tempr;
    //power_det[count_det] = powerread();
    ch4_det[count_det] = ch4read();
    co_det[count_det] = coread();
    hum_det[count_det] = humread();
    vel_det[count_det] = wvread();
    wdr_det[count_det] = wdrread();
    co2_det[count_det] = co2read();
    count_det++;
    Serial.println(count_det);
    if (count_det == 6)
    {
      temp_men[count_men] = (temp_det[0] + temp_det[1] + temp_det[2] + temp_det[3] + temp_det[4] + temp_det[5]) / 6;
      //power_men[count_men] = (power_det[0] + power_det[1] + power_det[2] + power_det[3] + power_det[4] + power_det[5]) / 6;
      ch4_men[count_men] = (ch4_det[0] + ch4_det[1] + ch4_det[2] + ch4_det[3] + ch4_det[4] + ch4_det[5]) / 6;
      co_men[count_men] = (co_det[0] + co_det[1] + co_det[2] + co_det[3] + co_det[4] + co_det[5]) / 6;
      hum_men[count_men] = (hum_det[0] + hum_det[1] + hum_det[2] + hum_det[3] + hum_det[4] + hum_det[5]) / 6;
      vel_men[count_men] = (vel_det[0] + vel_det[1] + vel_det[2] + vel_det[3] + vel_det[4] + vel_det[5]) / 6;
      //Kondisi khusus
      if ((wdrread() >= 0 && wdrread() <= 22.5) && (wdrread() >= 337.5 && wdrread() <= 360))
      {
        wdr_men[count_men] = wdrread();
      }
      else
      {
        wdr_men[count_men] = (wdr_det[0] + wdr_det[1] + wdr_det[2] + wdr_det[3] + wdr_det[4] + wdr_det[5]) / 6;
      }
      co2_men[count_men] = (co2_det[0] + co2_det[1] + co2_det[2] + co2_det[3] + co2_det[4] + co2_det[5]) / 6;
      Serial.print("Data menit : ");
      Serial.println(count_men + 1);
      t = rtc.getTime();
      tahun = t.year;
      bulan = t.mon;
      tanggal = t.date;
      jam = t.hour;
      menit = t.min;
      detik = t.sec;

      Serial.println(vel_men[count_men]);
      Serial.println(wdr_men[count_men]);
      Serial.println(temp_men[count_men]);
      Serial.println(ch4_men[count_men]);
      Serial.println(co_men[count_men]);
      Serial.println(co2_men[count_men]);
      Serial.println(hum_men[count_men]);
      Serial.println(Energy);
      Serial.println(Lat, 6);
      Serial.println(Lon, 6);
      //==================================================
      //Penyimpanan File pada SD shield
      //===================================================
      dataFile = SD.open("log.txt", FILE_WRITE); //Membaca SD
      if (dataFile)
      {
        //Station
        dataFile.print("st1");
        dataFile.print(",");
        //Tanggal
        dataFile.print(tahun);
        dataFile.print("-");
        dataFile.print(bulan);
        dataFile.print("-");
        dataFile.print(tanggal);
        dataFile.print(",");
        //Waktu
        dataFile.print(jam);
        dataFile.print(":");
        dataFile.print(menit);
        dataFile.print(":");
        dataFile.print(detik);
        dataFile.print(",");
        //Suhu
        dataFile.print(temp_men[count_men]);
        dataFile.print(",");
        //Kecepatan angin
        dataFile.print(vel_men[count_men]);
        dataFile.print(",");
        //Arah angin
        dataFile.print(wdr_men[count_men]);
        dataFile.print(",");
        //Karbon monoksida
        dataFile.print(co_men[count_men]);
        dataFile.print(",");
        //Metan
        dataFile.print(ch4_men[count_men]);
        dataFile.print(",");
        //Karbon Dioksida
        dataFile.print(co2_men[count_men]);
        dataFile.print(",");
        //Kelembaban
        dataFile.print(hum_men[count_men]);
        dataFile.print(",");
        //Power
        dataFile.print(Energy);
        dataFile.print(",");
        //Lokasi
        dataFile.print(Lat, 6);
        dataFile.print(",");
        dataFile.print(Lon, 6);
        dataFile.print(",");
        dataFile.println();
        dataFile.close();
      }
      else
      {
        Serial.println("Error opening file");
      }
      dataFile.flush();

      dataFile = SD.open("log.txt");
      if (dataFile) {
        while (dataFile.available()) {
          Serial.write(dataFile.read());
        }
      }
      dataFile.close();
      //==================================================
      count_men++;
      if (count_men == 3)
      {
        count_men = 0;
        kirim_ftp();
        if (errorcond == 1)
        {
          errorcond = 0;
          error++;
          Serial.println("Error cuy");
          if (error == 2)
          {
            error = 0;
            resetFunc();
          }
        }
        else
        {
          Serial.println("Hapus file log.txt");
          SD.remove("log.txt");
          error = 0;
        }
      }

      if (((temp_men[count_men] >= 40) && (co2_men[count_men] >= 5000) && (co_men[count_men] >= 25)) || (error == 1)) //Kondisi Force major
      {
        Serial.println("Kondisi Force Major");
        kirim_real_time();
      }
      count_det = 0;
    }
    count_time = 0;
  }
}
