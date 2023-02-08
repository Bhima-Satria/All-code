//Program monitoring pada TPA
//======================================

//Header program
#include <SoftwareSerial.h>
#include <Wire.h>
#include <SPI.h>
#include <LiquidCrystal_I2C.h>
#include <DS3231.h>
#include <SD.h>
#include "co.h"
#include "ch4.h"
#include "co2.h"
#include "led.h"
#include "temperature.h"
#include "Humidity.h"
#include "power.h"
#include "winddirection.h"
#include "windvelocity.h"
char g = '>';

//Definisi untuk LCD 20x4
#define I2C_ADDR 0x27
#define Rs_pin  0
#define Rw_pin  1
#define En_pin  2
#define BACKLIGHT_PIN 3
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

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

//Definisi untuk GSM
#define DEBUG true
String response = "";

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
float power_det[6];
float ch4_det[6];
float co_det[6];
float co2_det[6];
int hum_det[6];
int wdr_det[6];
float vel_det[6];
//Variabel untuk menyimpan nilai tiap menit
float temp_men[15];
float power_men[15];
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
  Serial.begin(9600);
  //Setup GSM modul
  //ser.begin(4800);
  //set_gsm();
//  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.begin();
  lcd.createChar(0, panah);
  lcd.print(">");
  //Output Relay/Pendingin
  pinMode (18, OUTPUT);
  pinMode (19, OUTPUT);
  
  //Setup SD shield
  
  if (!SD.begin(SS_SD))
  {
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("Card initialized.");

  //Mengatur Jam
  rtc.begin();
  //rtc.setDOW(TUESDAY);
  //rtc.setTime(22,07,0);
  //rtc.setDate(4,8,2019);

  /*
    //Mengecek file yang tersimpan
    if (SD.exists("log.txt")) {
      Serial.println("log.txt sudah ada");
      kirim_ftp();
      SD.remove("log.txt");
    }
    else {
      Serial.println("log.txt belum ada");
    }
  */
}

void loop()
{
  t=rtc.getTime();
  //rstactive();//Fungsi reset otomatis
  createCustomCharacters();
  printFrame();
  lcd.setCursor(5, 1);
  lcd.print(rtc.getDateStr());
  lcd.setCursor(6, 2);
  lcd.print(rtc.getTimeStr());

  //Serial.print("suhu: ");
  //Serial.println(tempread());
  Serial.print("Kelembaban: ");
  Serial.println(humread());
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

//Aktivasi  reset
void resetFunc()
{
  digitalWrite(19, HIGH);
}

//Fungsi automatic reset
void rstactive() {
  if (vread() <= 7.5)
  {
    resetcond = 1;
  }
  if ((resetcond == 1) && (vread() >= 7.7))
  {
    resetFunc();
  }
}

//Fungsi untuk Modul GSM
//=========================================================================
String sendCommand(String command, const int timeout, boolean debug) {
  response = "";

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
void read_gsm()
{
  long int time = millis();
  while ( (time + 10000) > millis()) {
    while (ser.available()) {
      // The esp has data so display its output to the serial window
      char c = ser.read(); // read the next character.
      response += c;
    }
  }
}

void set_gsm() {
  Serial.print("Cek Module\n");
  sendCommand("AT\r\n", 5000, DEBUG);
  Serial.print("Cek Network\n");
  sendCommand("AT+COPS?\r\n", 5000, DEBUG);
  Serial.print("Cek Quality Signal\n");
  sendCommand("AT+CSQ\r\n", 5000, DEBUG);
  Serial.print("Set GPRS\n");
  sendCommand("AT+SAPBR=3,1,\"Contype\",\"GPRS\"\r\n", 5000, DEBUG);
  Serial.print("Set GPRS Operator\n");
  sendCommand("AT+SAPBR=3,1,\"APN\",\"CMNET\"\r\n", 5000, DEBUG);
  Serial.print("Activate GPRS\n");
  sendCommand("AT+SAPBR=1,1\r\n", 5000, DEBUG);
  Serial.print("Check IP\n");
  sendCommand("AT+SAPBR=2,1\r\n", 5000, DEBUG);
  Serial.print("Open Protocol HTTP\n");
  sendCommand("AT+HTTPINIT\r\n", 5000, DEBUG);
  Serial.print("Set DNS Identifier\n");
  sendCommand("AT+HTTPPARA=\"CID\",1\r\n", 5000, DEBUG);
  Serial.print("Open FTP Protocol\n");
  sendCommand("AT+FTPCID=1\r\n", 5000, DEBUG);
  Serial.print("Set FTP Server\n");
  sendCommand("AT+FTPSERV=\"ftp.lowcarbon-malang.id\"\r\n", 5000, DEBUG);
  Serial.print("Set FTP Username\n");
  sendCommand("AT+FTPUN=\"admin@lowcarbon-malang.id\"\r\n", 5000, DEBUG);
  Serial.print("Set FTP Password\n");
  sendCommand("AT+FTPPW=\"T3-UM2018\"\r\n", 5000, DEBUG);
  Serial.println("Set File Target\n");
  String cmd1 = "AT+FTPPUTNAME="; // Link ke skrip PHP
  cmd1 += '"';
  cmd1 += "kirim.txt";
  cmd1 += '"';
  cmd1 += "\r\n\r\n";
  sendCommand(cmd1, 2000, DEBUG);
  Serial.print("Set Destination Folder FTP\n");
  sendCommand("AT+FTPPUTPATH=\"/tpa/\"\r\n", 5000, DEBUG);
  sendCommand("AT+FTPPUT=1\r\n", 5000, DEBUG);
  sendCommand("AT+FTPPUT=2,0\r\n", 5000, DEBUG);
}

void kirim_ftp() {
  delay(5000);
  digitalWrite(ledftp, HIGH);
  digitalWrite(ledrt, LOW);
  Serial.print("Kirim ftp");
  sendCommand("AT+FTPPUT=1\r\n", 5000, DEBUG);
  //coba++;
  //if ((response.substring(response.length() - 7, response.length() - 2) == "ERROR") || (coba >= 2))
  if (response.substring(response.length() - 7, response.length() - 2) == "ERROR")
  {
    //coba = 0;
    errorcond = 1;
  }
  else
  {
    dataFile = SD.open("log.txt");
    String cmd2 = "AT+FTPPUT=2,";
    cmd2 += String(dataFile.size() - 2);
    cmd2 += "\r\n";
    sendCommand(cmd2, 8000, DEBUG);
    if (dataFile) {
      while (dataFile.available() - 2) {
        ser.write(dataFile.read());
      }
    }
    else {}
    //Serial.println(dataFile.size());
    dataFile.close();
    if ((response.substring(response.length() - 7, response.length() - 2) == "ERROR") || (response.substring(0, 5) == "ERROR"))
    {
      errorcond = 1;
    }
    else
    {
      do
      {
        if (kirimftp == 5)
        {
          resetFunc();
        }
        kirimftp++;
        //Upload Nama
        String cmd5 = "AT+HTTPPARA=\"URL\",\"lowcarbon-malang.id/system/station/"; // Link ke skrip PHP
        //Kode Station
        cmd5 += "inject";
        cmd5 += '"';
        cmd5 += "\r\n\r\n";
        sendCommand(cmd5, 3000, DEBUG);
        String cmd6 = "AT+HTTPPARA=\"URL\",\"lowcarbon-malang.id/system/station/"; // Link ke skrip PHP
        //Kode Station
        cmd6 += "inject";
        cmd6 += '"';
        cmd6 += "\r\n\r\n";
        sendCommand(cmd6, 3000, DEBUG);
        delay(5000);
        Serial.println("Sending Process");
        String action1 = "AT+HTTPACTION=0";
        action1 += "\r\n\r\n";
        sendCommand(action1, 8000, DEBUG);
        /*
          Serial.println("================");
          Serial.println("Hasil Parsing");
          Serial.println(response.substring(19, 21));
          Serial.println("================");
        */
        if ((response.substring(19, 21) == "OK") )
        {
          kondisi = 1;
          read_gsm();
          Serial.println(response);
        }
      } while (kondisi != 1);
      kondisi = 0;
    }
  }
  digitalWrite(ledftp, LOW);
  digitalWrite(ledrt, LOW);
}

void kirim_real_time() {
  digitalWrite(ledftp, LOW);
  digitalWrite(ledrt, HIGH);
  tempr = tempread();
  humr = humread();
  delay(1000);
  t=rtc.getTime();
  /*
    String cmd2 = "AT+HTTPPARA=\"URL\",\"mupou.pesc-um.com/insert.php?"; // Link ke skrip PHP
    cmd2 += "channel=5";
    cmd2 += "&nilai_metan=";
    cmd2 += String(20);
    cmd2 += "&nilai_ppm=";
    cmd2 += String(50);
    cmd2 += '"';
    cmd2 += "\r\n\r\n";
  */
  String cmd4 = "AT+HTTPPARA=\"URL\",\"lowcarbon-malang.id/system/station/insert/"; // Link ke skrip PHP
  //Kode Station
  cmd4 += "st/st1/";
  //Tanggal
  cmd4 += "d/";
  cmd4 += String(tahun);
  cmd4 += "-";
  cmd4 += String(bulan);
  cmd4 += "-";
  cmd4 += String(tanggal);
  //Waktu
  cmd4 += "/t/";
  cmd4 += String(jam);
  cmd4 += ":";
  cmd4 += String(menit);
  cmd4 += ":";
  cmd4 += String(detik);
  //Temperatur
  cmd4 += "/c/";
  cmd4 += String(temp_men[count_men]);
  //Kecepatan angin
  cmd4 += "/a/";
  cmd4 += String(vel_men[count_men]);
  //Arah angin
  cmd4 += "/aa/";
  cmd4 += String(wdr_men[count_men]);
  //Gas Metan
  cmd4 += "/ch4/";
  cmd4 += String(ch4_men[count_men]);
  //Gas Karbon Monoksida
  cmd4 += "/co/";
  cmd4 += String(co_men[count_men]);
  //Gas Karbon Dioksida
  cmd4 += "/co2/";
  cmd4 += String(co2_men[count_men]);
  //Kelembaban
  cmd4 += "/h/";
  cmd4 += String(hum_men[count_men]);
  //Tegangan
  cmd4 += "/v/";
  cmd4 += String(power_men[count_men]);
  cmd4 += '"';
  cmd4 += "\r\n\r\n";

  Serial.println("Sending Process");
  String action2 = "AT+HTTPACTION=0";
  action2 += "\r\n\r\n";
  sendCommand(cmd4, 3000, DEBUG);
  delay(5000);
  if ((response.substring(response.length() - 7, response.length() - 2) == "ERROR") || (response.substring(response.length() - 7, response.length() - 2) == ""))
  {
    Serial.println("Pertanda error");
    resetFunc();
  }
  sendCommand(action2, 5000, DEBUG);
  read_gsm();
  Serial.println(response);
  delay(5000);
  digitalWrite(ledftp, LOW);
  digitalWrite(ledrt, LOW);
}
//===========================================================================

void read_data()
{
  tempr = tempread(); //Temperature
  Serial.print(count_time);
  count_time++;
  if (count_time == 20)
  {
    temp_det[count_det] = tempr;
    power_det[count_det] = powerread();
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
      power_men[count_men] = (power_det[0] + power_det[1] + power_det[2] + power_det[3] + power_det[4] + power_det[5]) / 6;
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
      t=rtc.getTime();
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
      Serial.println(power_men[count_men]);
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
        //Tegangan
        dataFile.print(power_men[count_men]);
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

void menu()
{
  while (1)
  {
    pilih_awal(5);
    switch (tombol)
    {
      case 1:
        tampilan_menu(0);
        if (digitalRead(ok) == LOW)
        {
          delay(400);
          ganti_nilai_tpa = true;
          while (4)
          {
            tampilan_menu(0);
            if (digitalRead(back) == LOW)
            {
              delay(400);
              ganti_nilai_tpa = false;
              break;
            }
          }
        }

        break;

      case 2:
        if (kolom == 1)
        {
          tampilan_menu(1);
          if (digitalRead(ok) == LOW)
          {
            delay(10);
            lcd.clear();
            temp();
          }
        }
        if (kolom == 2)
        {
          tampilan_menu(3);
          if (digitalRead(ok) == LOW)
          {
            delay(10);
            lcd.clear();
            ch4();
          }
        }
        break;

      case 3:
        if (kolom == 1)
        {
          tampilan_menu(2);
          if (digitalRead(ok) == LOW)
          {
            delay(10);
            lcd.clear();
            power();
          }
        }

        if (kolom == 2)
        {
          tampilan_menu(4);
          if (digitalRead(ok) == LOW)
          {
            delay(10);
            lcd.clear();
            co();
          }
        }
        break;

      case 4:
        if (kolom == 1)
        {
          tampilan_menu(5);
          if (digitalRead(ok) == LOW)
          {
            delay(10);
            lcd.clear();
            hum();
          }
        }
        if (kolom == 2)
        {
          tampilan_menu(7);
          if (digitalRead(ok) == LOW)
          {
            delay(10);
            lcd.clear();
            wdr();
          }
        }
        break;

      case 5:
        if (kolom == 1)
        {
          tampilan_menu(6);
          if (digitalRead(ok) == LOW)
          {
            delay(10);
            lcd.clear();
            vel();
          }
        }

        if (kolom == 2)
        {
          tampilan_menu(8);
          if (digitalRead(ok) == LOW)
          {
            delay(10);
            lcd.clear();
            co2();
          }
        }
        break;


      default:
        tampilan_menu(1);
        break;
    }
    if (digitalRead(back) == LOW)
    {
      delay(100);
      lcd.clear();
      break;
    }
  }
}

/*void printTime(int character, int line, tmElements_t tm)
{
  String seconds, minutes;
  lcd.setCursor(character, line);
  lcd.print(tm.Hour);
  lcd.print(":");
  if (tm.Minute < 10)
  {
    minutes = "0" + String(tm.Minute);
    lcd.print(minutes);
  } else
  {
    lcd.print(tm.Minute);
  }
  lcd.print(":");
  if (tm.Second < 10)
  {
    seconds = "0" + String(tm.Second);
    lcd.print(seconds);
  } else
  {
    lcd.print(tm.Second);
  }
}

/*void printDate(int character, int line, tmElements_t tm)
{
  lcd.setCursor(character, line);
  lcd.print(tm.Day);
  lcd.print("-");
  lcd.print(tm.Month);
  lcd.print("-");
  lcd.print(tmYearToCalendar(tm.Year));
}
*/
void printFrame()
{
  lcd.setCursor(1, 0);
  lcd.print("------------------");
  lcd.setCursor(1, 3);
  lcd.print("------------------");
  lcd.setCursor(0, 1);
  lcd.write(byte(0));
  lcd.setCursor(0, 2);
  lcd.write(byte(0));
  lcd.setCursor(19, 1);
  lcd.write(byte(0));
  lcd.setCursor(19, 2);
  lcd.write(byte(0));
  lcd.setCursor(0, 0);
  lcd.write(byte(1));
  lcd.setCursor(19, 0);
  lcd.write(byte(2));
  lcd.setCursor(0, 3);
  lcd.write(byte(3));
  lcd.setCursor(19, 3);
  lcd.write(byte(4));
}

void createCustomCharacters()
{
  lcd.createChar(0, verticalLine);
  lcd.createChar(1, char1);
  lcd.createChar(2, char2);
  lcd.createChar(3, char3);
  lcd.createChar(4, char4);
}

void pilih_awal(int tipe_menu)
{
  if (digitalRead(atas) == LOW)
  {
    delay(10);
    if (tombol < 2)
    {
      tombol = tipe_menu;
    }
    else
      tombol = tombol - 1;
  }
  //Serial.print("nilai tombol atas =");
  //Serial.println(digitalRead(atas));

  if (digitalRead(bawah) == LOW)
  {
    delay(10);
    if (tombol > tipe_menu - 1)
    {
      tombol = 1;
    }
    else
      tombol = tombol + 1;
  }

  if (digitalRead(kanan) == LOW && kolom == 1)
  {
    delay(400);
    kolom = 2;
  }
  if (digitalRead(kanan) == LOW && kolom == 2)
  {
    delay(400);
    kolom = 1;
    if (tombol == 5) tombol = 1;
    else
      tombol++;
  }
  if (digitalRead(kiri) == LOW && kolom == 2)
  {
    delay(400);
    kolom = 1;
  }
  if (digitalRead(kiri) == LOW && kolom == 1)
  {
    delay(400);
    kolom = 2;
    if (tombol == 1) tombol = 5;
    else
      tombol--;
  }

  //Serial.print("nilai tombol bawah =");
  //Serial.println(digitalRead(bawah));
  //Serial.println(tombol);
  //Serial.print("nilai kolom = ");
  //Serial.println(kolom);
  //Serial.print("nilai tombol kanan =");
  //Serial.println(digitalRead(kanan));
}

void tampilan_menu(int a)
{
  lcd.clear();
  read_data();
  lcd.setCursor(6, 1);
  lcd.print("TPA");
  if (a != 0)
  {
    //Serial.print("nilai a=");
    //Serial.println(a);
    if (a < 3)   lcd.setCursor(0, a + 1);
    if (a > 2 && a < 5) lcd.setCursor(11, a - 1);
    if (a > 4 && a < 7) lcd.setCursor(0, a - 3);
    if (a > 6) lcd.setCursor(11, a - 5);
    lcd.print(">");
  }
  else
  {
    if (ganti_nilai_tpa == true)
    {
      if (digitalRead(kanan) == LOW)
      {
        delay(400);
        nilai_tps++;
      }
      if (digitalRead(kiri) == LOW && !nilai_tps < 1)
      {
        delay(400);
        nilai_tps--;
      }
      lcd.setCursor(9, 1);
    }
    else
      lcd.setCursor(5, 1);
    lcd.print(">");
  }

  if (a < 5)
  {
    lcd.setCursor(1, 2);
    lcd.print("Temp:");
    lcd.print(tempr);
    lcd.setCursor(8, 2); lcd.print((char)223); lcd.print("C ");
    lcd.setCursor(1, 3);
    lcd.print("P   :");
    lcd.print(powerread());
    lcd.setCursor(10, 3);
    lcd.print("mW ");
    lcd.setCursor(12, 2);
    lcd.print("CH4 :");
    lcd.print(ch4read());
    lcd.setCursor(12, 3);
    lcd.print("CO  :");
    lcd.print(coread());
    lcd.setCursor(0, 0);
    lcd.print("  ");
    lcd.setCursor(0, 1);
    lcd.print("  ");
    lcd.setCursor(10, 1);
    lcd.print("000");
    if (nilai_tps < 10)
    {
      lcd.setCursor(12, 1);
    }
    if (nilai_tps >= 10 && nilai_tps < 100)
    {
      lcd.setCursor(11, 1);
    }
    if (nilai_tps >= 100)
    {
      lcd.setCursor(10, 1);
    }
    lcd.print(nilai_tps);
  }
  if (a > 4)
  {
    lcd.setCursor(1, 2);
    lcd.print("Hum :");
    lcd.print(humread()); lcd.print("%");
    lcd.setCursor(1, 3);
    lcd.print("Vel :");
    lcd.print(wvread());
    lcd.setCursor(8, 3);
    lcd.print("m/s");
    lcd.setCursor(12, 2);
    lcd.print("WDR :");
    //lcd.print(wdrread()); lcd.print((char)223);
    lcd.print(wdrconv());
    lcd.setCursor(12, 3);
    lcd.print("CO2 :");
    lcd.print(co2read());
    lcd.setCursor(0, 0);
    lcd.print(" ");
    lcd.setCursor(0, 1);
    lcd.print(" ");
    lcd.setCursor(10, 1);
    lcd.print("000");
    if (nilai_tps < 10)
    {
      lcd.setCursor(12, 1);
    }
    if (nilai_tps >= 10 && nilai_tps < 100)
    {
      lcd.setCursor(11, 1);
    }
    if (nilai_tps >= 100)
    {
      lcd.setCursor(10, 1);
    }
    lcd.print(nilai_tps);
  }
  lcd.setCursor(0, 0);
  lcd.print("     ");
  lcd.setCursor(0, 1);
  lcd.print("     ");
  refresh();
}

void temp() {
  while (3)
  {
    read_data();
    lcd.setCursor(4, 0);
    lcd.print("Temperature");
    pilih_awal(15);
    //Serial.print("nilai tombol =");
    //Serial.println(tombol);
    if (tombol < 4)
    {
      lcd.setCursor(1, 1);
      lcd.print("1. "); lcd.print(temp_men[0]); lcd.print((char)223); lcd.print("C ");
      lcd.setCursor(1, 2);
      lcd.print("2. "); lcd.print(temp_men[1]); lcd.print((char)223); lcd.print("C ");
      lcd.setCursor(1, 3);
      lcd.print("3. "); lcd.print(temp_men[2]); lcd.print((char)223); lcd.print("C ");
      lcd.setCursor(0, tombol);
      lcd.print(">");
    }
    refresh();
    lcd.clear();
    //Serial.print(digitalRead(back));
    if (digitalRead(back) == LOW)
    {
      delay(250);
      break;
    }
  }
}

void power() {
  while (3)
  {
    read_data();
    lcd.setCursor(2, 0);
    lcd.print("Tegangan");
    pilih_awal(15);
    //Serial.print("nilai tombol =");
    //Serial.println(tombol);
    if (tombol < 4)
    {
      lcd.setCursor(1, 1);
      lcd.print("1. "); lcd.print(power_men[0]); lcd.print(" V");
      lcd.setCursor(1, 2);
      lcd.print("2. "); lcd.print(power_men[1]); lcd.print(" V");
      lcd.setCursor(1, 3);
      lcd.print("3. "); lcd.print(power_men[2]); lcd.print(" V");
      lcd.setCursor(0, tombol);
      lcd.print(">");
    }
    refresh();
    lcd.clear();
    //Serial.print(digitalRead(back));
    if (digitalRead(back) == LOW)
    {
      delay(250);
      break;
    }
  }
}

void ch4() {
  while (3)
  {
    read_data();
    lcd.setCursor(4, 0);
    lcd.print("Metana");
    pilih_awal(15);
    //Serial.print("nilai tombol =");
    //Serial.println(tombol);
    if (tombol < 4)
    {
      lcd.setCursor(1, 1);
      lcd.print("1. "); lcd.print(ch4_men[0]); lcd.print(" ppm");
      lcd.setCursor(1, 2);
      lcd.print("2. "); lcd.print(ch4_men[1]); lcd.print(" ppm");
      lcd.setCursor(1, 3);
      lcd.print("3. "); lcd.print(ch4_men[2]); lcd.print(" ppm");
      lcd.setCursor(0, tombol);
      lcd.print(">");
    }
    refresh();
    lcd.clear();
    //Serial.print(digitalRead(back));
    if (digitalRead(back) == LOW)
    {
      delay(250);
      break;
    }
  }
}

void co() {
  while (3)
  {
    read_data();
    lcd.setCursor(1, 0);
    lcd.print("Karbon Monosida");
    pilih_awal(15);
    //Serial.print("nilai tombol =");
    //Serial.println(tombol);
    if (tombol < 4)
    {
      lcd.setCursor(1, 1);
      lcd.print("1. "); lcd.print(co_men[0]); lcd.print(" ppm");
      lcd.setCursor(1, 2);
      lcd.print("2. "); lcd.print(co_men[1]); lcd.print(" ppm");
      lcd.setCursor(1, 3);
      lcd.print("3. "); lcd.print(co_men[2]); lcd.print(" ppm");
      lcd.setCursor(0, tombol);
      lcd.print(">");
    }
    refresh();
    lcd.clear();
    //Serial.print(digitalRead(back));
    if (digitalRead(back) == LOW)
    {
      delay(250);
      break;
    }
  }
}

void hum() {
  while (3)
  {
    read_data();
    lcd.setCursor(4, 0);
    lcd.print("Humidity");
    pilih_awal(15);
    //Serial.print("nilai tombol =");
    //Serial.println(tombol);
    if (tombol < 4)
    {
      lcd.setCursor(1, 1);
      lcd.print("1. "); lcd.print(hum_men[0]); lcd.print(" %");
      lcd.setCursor(1, 2);
      lcd.print("2. "); lcd.print(hum_men[1]); lcd.print(" %");
      lcd.setCursor(1, 3);
      lcd.print("3. "); lcd.print(hum_men[2]); lcd.print(" %");
      lcd.setCursor(0, tombol);
      lcd.print(">");
    }
    refresh();
    lcd.clear();
    //Serial.print(digitalRead(back));
    if (digitalRead(back) == LOW)
    {
      delay(250);
      break;
    }
  }
}

void vel() {
  while (3)
  {
    read_data();
    lcd.setCursor(1, 0);
    lcd.print("Wind Velocity");
    pilih_awal(15);
    //Serial.print("nilai tombol =");
    //Serial.println(tombol);
    if (tombol < 4)
    {
      lcd.setCursor(1, 1);
      lcd.print("1. "); lcd.print(vel_men[0]); lcd.print(" m/s");
      lcd.setCursor(1, 2);
      lcd.print("2. "); lcd.print(vel_men[1]); lcd.print(" m/s");
      lcd.setCursor(1, 3);
      lcd.print("3. "); lcd.print(vel_men[2]); lcd.print(" m/s");
      lcd.setCursor(0, tombol);
      lcd.print(">");
    }
    refresh();
    lcd.clear();
    //Serial.print(digitalRead(back));
    if (digitalRead(back) == LOW)
    {
      delay(250);
      break;
    }
  }
}

void wdr() {
  while (3)
  {
    read_data();
    lcd.setCursor(1, 0);
    lcd.print("Arah Mata Angin");
    pilih_awal(15);
    //Serial.print("nilai tombol =");
    //Serial.println(tombol);
    if (tombol < 4)
    {
      lcd.setCursor(1, 1);
      lcd.print("1. "); lcd.print(wdr_men[0]); lcd.print((char)223);
      lcd.setCursor(1, 2);
      lcd.print("2. "); lcd.print(wdr_men[1]); lcd.print((char)223);
      lcd.setCursor(1, 3);
      lcd.print("3. "); lcd.print(wdr_men[2]); lcd.print((char)223);
      lcd.setCursor(0, tombol);
      lcd.print(">");
    }
    refresh();
    lcd.clear();
    //Serial.print(digitalRead(back));
    if (digitalRead(back) == LOW)
    {
      delay(250);
      break;
    }
  }
}

void co2() {
  while (3)
  {
    read_data();
    lcd.setCursor(1, 0);
    lcd.print("Karbon Dioksida");
    pilih_awal(15);
    //Serial.print("nilai tombol =");
    //Serial.println(tombol);
    if (tombol < 4)
    {
      lcd.setCursor(1, 1);
      lcd.print("1. "); lcd.print(co2_men[0]); lcd.print(" ppm");
      lcd.setCursor(1, 2);
      lcd.print("2. "); lcd.print(co2_men[1]); lcd.print(" ppm");
      lcd.setCursor(1, 3);
      lcd.print("3. "); lcd.print(co2_men[2]); lcd.print(" ppm");
      lcd.setCursor(0, tombol);
      lcd.print(">");
    }
    refresh();
    lcd.clear();
    //Serial.print(digitalRead(back));
    if (digitalRead(back) == LOW)
    {
      delay(250);
      break;
    }
  }
}
