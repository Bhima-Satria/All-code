#include <SPI.h>
#include <Ethernet.h>
#include <EEPROM.h>
#include <DS3231.h>
#include <SD.h>

// EPORPORASI
byte mac[]= {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

int IPa =0;
int IPb =1;
int IPc =2;
int IPd =3;

int a;
int b;
int c;
int d;

int Simpan_ID=5; //Untuk Alamat 5-11
int Simpan_Pj=41; // Untuk Pajak 41-66
//int Simpan_Tgl=12; //Untuk Tgl 12-18
//int Simpan_Jam=19; //Untuk Jam 19-30
//int Simpan_Rp=31; // Untuk Rp 31-40

String tgl;
String jam;
String Rp;
String ID;
String ID_Pj;
String eporporasi;

//RTC
int Jam1;
int Menit1;
int Detik1;

//SIM 800L
String apn = "internet";               //APN
String apn_u = "";                     //APN-Username
String apn_p = "";                     //APN-Password
String url = "http://siprida.databumi.id/etax/Api/getPorporasi.php?";  //URL for HTTP-POST-REQUEST

//Indikator
int Led_Data = 2;
int Led_Lan  = 6;
int Led_Pwr  = 8;

//SD Card
File myFile;

// Tanggal+Jam+Rp

String commandStr;

EthernetServer server(80); //Miso Mosi Clk Ss menyesuaikan Arduino
DS3231 rtc(SDA, SCL); //Kaki SDA=20 SCL=21

void SimpanEEPROMChar(char *p, int adr);
void (* Reset) (void) = 0;

void setup() {
  
  pinMode(23, OUTPUT);
  digitalWrite(23, LOW);
  
  Serial1.begin(9600); // Kaki Rx=19 Tx=18 crosh With Sim800l TX=RX / RX=TX
  Serial.begin(9600);
  
  pinMode(Led_Data, OUTPUT);
  pinMode(Led_Lan, OUTPUT);
  pinMode(Led_Pwr, OUTPUT);

  digitalWrite(Led_Pwr, LOW);
  digitalWrite(Led_Data, HIGH);
  digitalWrite(Led_Lan, HIGH);
  
// Etehrnet Shield
// EEPROM.write(IPa, 192);
// EEPROM.write(IPb, 168);
// EEPROM.write(IPc, 1);
// EEPROM.write(IPd, 1);

 a=EEPROM.read(IPa);
 b=EEPROM.read(IPb);
 c=EEPROM.read(IPc);
 d=EEPROM.read(IPd);
 
  IPAddress ip(a,b,c,d);
  
  Ethernet.begin(mac,ip);
  server.begin();
  rtc.begin();
  Serial.print("Server is at : ");
  Serial.println(Ethernet.localIP());
  delay(1000);
  

// SIM800L
  delay(5000);
  Serial1.println("AT");
  runsl();//Print GSM Status an the Serial Output;
  delay(4000);
  Serial1.println("AT+SAPBR=3,1,Contype,GPRS");
  runsl();
  delay(100);
  Serial1.println("AT+SAPBR=3,1,APN," + apn);
  runsl();
  delay(1000);
  Serial.println("SIM800 Start....");
  server.write("E-Porporasi Ready....");
}

void loop() {
  EthernetClient client = server.available();
  if (client.available()>0){
    char c = client.read();
       
    if (c != '\n'){
      commandStr += c;
    }
    else {
      Serial.println("Command:" + commandStr + '\n' + "Length:"  + commandStr.length());
      processCommand(commandStr);
      server.write(client.read());
      commandStr="";
    }
  }

}

void processCommand(String cmd) {
int panjang = cmd.length();

  server.write("Get Porporasi");
  //Request Stempel E-Stamp 
  if (cmd.substring(0,2) =="90") {
   digitalWrite(Led_Lan, LOW);
   delay(100);
   digitalWrite(Led_Lan, HIGH);
   if (cmd.length() == 28){
 
   server.write("E-Stamp : ");
   tgl  = cmd.substring(3,11);
   jam  = cmd.substring(12,18);
   Rp   = cmd.substring(19,28);
   
  Serial.print(tgl + '\t');
  Serial.print(jam + '\t');
  Serial.println(Rp + '\t');
  
   char E_Tanggal [10]; //Asli 8 Char
   char E_Jam [10]; //Asli 6 Char
   char E_Rp [10]; // Asli 9 Char

   tgl.toCharArray(E_Tanggal, 10);
   jam.toCharArray(E_Jam, 10); 
   Rp.toCharArray(E_Rp, 10);

   String epor1 = String(E_Jam[3]) + String(E_Jam[2]) + String(E_Rp[3]);
   String epor2 = String(E_Jam[4]) + String(E_Jam[3]) + String(E_Rp[4]);
   String epor3 = String(E_Jam[5]) + String(E_Jam[4]) + String(E_Rp[5]);
   String epor4 = String(E_Tanggal[4]) + String(E_Jam[5]) + String(E_Rp[6]);
   String epor5 = String(E_Tanggal[5]) + String(E_Jam[3]) + String(E_Rp[7]);
   String epor6 = String(E_Tanggal[6]) + String(E_Jam[0]) + String(E_Rp[8]);
   String epor11 = String(E_Tanggal[7]) + String(E_Jam[1]) + String(E_Rp[7]);
   String epor12 = String(E_Rp[0]) + String(E_Jam[2]) + String(E_Rp[6]);
   String epor13 = String(E_Rp[1]) + String(E_Jam[3]) + String(E_Rp[5]);
   String epor14 = String(E_Rp[2]) + String(E_Jam[4]) + String(E_Rp[4]);
   String epor15 = String(E_Rp[3]);
   String epor16 = String(E_Rp[4]);   

   eporporasi = epor1 + epor2 + epor3 + epor4 + epor5 + epor6 + epor11 + epor12 + epor13 + epor14 + epor15 + epor16;
   server.print(eporporasi);
 
    //Kirim Data Server
    digitalWrite(Led_Data, LOW);
    gsm_sendhttp();
    server.write(";90,OK");
    SDcard();
    delay(500);
    digitalWrite(Led_Data, HIGH);
   } else {
    server.write("Syntax Error!");
   }
  }
   
  //Baca + Ganti ID Pajak
  else if (cmd.substring(0,2)=="91") {
   digitalWrite(Led_Lan, LOW);
   delay(100);
   digitalWrite(Led_Lan, HIGH);
   
    server.write("ID_pajak : ");
    if (cmd.length() == 2 ) {
      for (int x=0; x<=25 ;x++){
      server.write(EEPROM.read(Simpan_Pj+x));
     }
      server.write(";91,OK");
    } else if (cmd.length() == 28){
    ID_Pj = cmd.substring(3,28);
    char ID_Pajak [30];
    ID_Pj.toCharArray(ID_Pajak, 30);
    SimpanEEPROMChar(ID_Pajak, Simpan_Pj);
    server.write(";91,Update,OK");      
    }
    else server.write("Syntax Error!");
     
  }

  //Baca+Ganti ID Alat
  else if (cmd.substring(0,2)=="92") {
   digitalWrite(Led_Lan, LOW);
   delay(100);
   digitalWrite(Led_Lan, HIGH);
   
    server.write("ID_Alat :");
    if (cmd.length() == 2 ) {
      for (int z=0; z<=6 ; z++){
       server.write(EEPROM.read(Simpan_ID+z));
      }
      server.write(";92,OK");
    } 
    else if (cmd.length() == 10) {
    ID = cmd.substring(3,10);
    char ID_Alat [10];
    ID.toCharArray(ID_Alat, 10);
    SimpanEEPROMChar(ID_Alat, Simpan_ID);
      for (int z=0; z<=6 ; z++){
       server.write(EEPROM.read(Simpan_ID+z));
      }
      server.write(";92,Update,OK");
    }
      else server.write ("Syntax Error!");    
  }

  //Baca RTC
  else if (cmd.substring(0,2) =="93") {
   digitalWrite(Led_Lan, LOW);
   delay(100);
   digitalWrite(Led_Lan, HIGH);
   
    if (cmd.length() == 2) {
    server.write("Jam :");
    server.write(rtc.getTimeStr());
    server.write(";93,OK");
    } else {
      String Jam_RTC    = cmd.substring(3,5);
      String Menit_RTC  = cmd.substring(6,8);
      String Detik_RTC  = cmd.substring(9,11);
       Jam1    = Jam_RTC.toInt();
       Menit1  = Menit_RTC.toInt();
       Detik1  = Detik_RTC.toInt();
      rtc.setTime(Jam1, Menit1, Detik1);
      server.write(rtc.getTimeStr());
      server.write(";93,Update,OK");
    }
  }

  //Atur Alamat IP
  else if (cmd.substring(0,2) =="94") {
   digitalWrite(Led_Lan, LOW);
   delay(100);
   digitalWrite(Led_Lan, HIGH);

   if (cmd.length()==18){
    server.write("Set_IP");
    String f = cmd.substring(3,6);
    String g = cmd.substring(7,10);
    String h = cmd.substring(11,14);
    String i = cmd.substring(15,18);

    a=f.toInt();
    b=g.toInt();
    c=h.toInt();
    d=i.toInt();
    
    Serial.print("New IP: " + String(a) + ".");
    Serial.print(String(b)+".");
    Serial.print(String(c)+".");
    Serial.print(String(d));
    
    EEPROM.write(IPa, a);
    EEPROM.write(IPb, b);
    EEPROM.write(IPc, c);
    EEPROM.write(IPd, d);
    delay(1000);
    server.write(";94,OK");
   }
   else server.write("Syntax Error");
  }
  else if (cmd.substring(0,2) =="95") {
   digitalWrite(Led_Lan, LOW);
   delay(100);
   digitalWrite(Led_Lan, HIGH);
   server.write("Reset Eporporasi!");
   digitalWrite(Led_Pwr, HIGH);
   delay(200);
   digitalWrite(Led_Pwr, LOW);
   delay(200);
   digitalWrite(Led_Pwr, HIGH);
   delay(200);
   digitalWrite(Led_Pwr, LOW);
   delay(200);
   digitalWrite(Led_Pwr, HIGH);
   delay(200);
   digitalWrite(Led_Pwr, LOW);
   delay(200);
   digitalWrite(Led_Pwr, HIGH);
   Reset();
   }
}


void gsm_sendhttp() {

  char Kirim_ID;
      for (int y=0; y<=6 ; y++){
       Kirim_ID = EEPROM.read(Simpan_ID+y);
      }
  
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
  Serial1.println("AT+HTTPPARA=URL," + url + "porporasi=" + eporporasi + "&devid=" + String(Kirim_ID)  + "&total=" + Rp + "&date=" + tgl +"&time=" + jam);
  runsl();
  delay(100);
  Serial1.println("AT+HTTPPARA=CONTENT,application/x-www-form-urlencoded");
  runsl();
  delay(100);
  Serial1.println("AT+HTTPDATA=192,10000");
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


void SimpanEEPROMChar(char *p, int adr){
  char Dt;
  for (int i=0; i<26; i++){
   Dt=*p;
   if (Dt==0){
    break;
   } 
   EEPROM.write(adr, Dt);
   p++;
   adr++;
  }
}


void runsl() {
  while (Serial1.available()) {
    Serial.write(Serial1.read());
  }
}

void SDcard (){

  digitalWrite(23, HIGH);
  delay(100);
  
   myFile = SD.open("log_File.txt", FILE_WRITE);
   String Log_Tgl = rtc.getDateStr();
   String Log_Jam = rtc.getTimeStr();
   

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to Log_File.txt...");
    myFile.println("Tanggal="+ Log_Tgl + " ;Jam=" + Log_Jam + " ;No Porporasi=" + eporporasi + " ;Transaksi=" + Rp);
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening Log_File.txt");
  }

   digitalWrite(23, LOW);
}
