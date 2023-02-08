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

int a1,b1,c1,d1;

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
String cmd,result,gettime;
String gsm_result,Status;

char notifikasi[30];

//RTC
int Jam1;
int Menit1;
int Detik1;

//SIM 800L
String apn = "internet";               //APN
String apn_u = "";                     //APN-Username
String apn_p = "";                     //APN-Password
String url = "http://siprida.databumi.id/etax/Api/getPorporasi.php?";  //URL for HTTP-POST-cmd

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
// EEPROM.write(IPd, 100);

 a1=EEPROM.read(IPa);
 b1=EEPROM.read(IPb);
 c1=EEPROM.read(IPc);
 d1=EEPROM.read(IPd);
 
  IPAddress ip(a1,b1,c1,d1);
  
  Ethernet.begin(mac,ip);
  server.begin();
  rtc.begin();
  Serial.print("Server is at : ");
  Serial.println(Ethernet.localIP());
  delay(1000);


// SIM800L
  delay(2000);
  Serial1.println("AT");
  AT_respon();//Print GSM Status an the Serial Output;
  delay(2000);
  Serial1.println("AT+SAPBR=3,1,Contype,GPRS");
  AT_respon();
  delay(100);
  Serial1.println("AT+SAPBR=3,1,APN," + apn);
  AT_respon();
  delay(1000);
  Serial.println("SIM800 Start....");
  
}

void loop() {

// listen for incoming clients
  gettime=rtc.getTimeStr();
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http cmd ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        cmd += c ; 
        
        client.flush(); 
              
        if (c == '\n' && currentLineIsBlank) {  
           Serial.println(cmd.substring(5,7));
           Serial.println(cmd.length());
           
            //Get porporasi
              if(cmd.substring(5,7) == "90"){
                 digitalWrite(Led_Lan, LOW);
                 delay(200);
                 digitalWrite(Led_Lan, HIGH);
                 
                 if (cmd.length() == 362){

                   tgl  = cmd.substring(8,16);
                   jam  = cmd.substring(17,23);
                   Rp   = cmd.substring(24,33);
                   
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
           
                  //Kirim Data Server
                    digitalWrite(Led_Data, LOW);
                    gsm_sendhttp();
                    SDcard();
                    result = "Get Porposasi; Sukses";
                    delay(500);
                    digitalWrite(Led_Data, HIGH);
                                        
              }
              else eporporasi="Syntax Error!";
            }
            
            //Get ID_Pajak
            else if(cmd.substring(5,7) == "91"){
              digitalWrite(Led_Lan, LOW);
              delay(200);
              digitalWrite(Led_Lan, HIGH);
              
              if(cmd.length() == 336){
                for(int x=0; x<=25 ;x++){
                 notifikasi[x]= EEPROM.read(Simpan_Pj+x);
                 result += notifikasi[x];
                }
                Serial.println(result);
              }
              else if(cmd.length() == 362){
                ID_Pj = cmd.substring(8,33);
                Serial.println(ID_Pj);
                char ID_Pajak [25];
                ID_Pj.toCharArray(ID_Pajak, 25);
                SimpanEEPROMChar(ID_Pajak, Simpan_Pj);
                result="91,Update,OK 'ID pajak berhasil di update' ";
              }
              else result="Syntax Error!";
            }

            //Baca & Ganti ID Alat
            else if(cmd.substring(5,7 )== "92"){
              digitalWrite(Led_Lan, LOW);
              delay(100);
              digitalWrite(Led_Lan, HIGH);      
              
              
              if(cmd.length() == 336){
                for (int z=0; z<7 ; z++){
                notifikasi[z]= EEPROM.read(Simpan_ID+z);  
                result += notifikasi[z];
                }
                Serial.println(notifikasi);    
                Serial.println(result);
              }
              else if(cmd.length() ==  344){
                ID = cmd.substring(8,15);
                char ID_Alat [7];
                ID.toCharArray(ID_Alat, 7);
                SimpanEEPROMChar(ID_Alat, Simpan_ID);
                  for (int z=0; z<7 ; z++){
                   notifikasi[z]=EEPROM.read(Simpan_ID+z);
                   result="92,Update,OK 'ID Alat berhasil di update' ";
                  }
                  Serial.println(result);
              }
              else result="Syntax Error!";
            }

            //Baca RTC
            else if(cmd.substring(5,7) == "93"){
             digitalWrite(Led_Lan, LOW);
             delay(100);
             digitalWrite(Led_Lan, HIGH);
             
             if (cmd.length() == 336){
              gettime=rtc.getTimeStr();
             } 
             else if(cmd.length() == 345){
               String Jam_RTC    = cmd.substring(8,10);
               String Menit_RTC  = cmd.substring(11,13);
               String Detik_RTC  = cmd.substring(14,16);
               Jam1    = Jam_RTC.toInt();
               Menit1  = Menit_RTC.toInt();
               Detik1  = Detik_RTC.toInt();
               rtc.setTime(Jam1, Menit1, Detik1);
               gettime=rtc.getTimeStr();
               result="93,Update,OK 'Jam berhasil di update' ";
             }
             else gettime="Syntax Error!";
            }

            //Atur Alamat IP
            else if(cmd.substring(5,7) == "94"){
             digitalWrite(Led_Lan, LOW);
             delay(100);
             digitalWrite(Led_Lan, HIGH);

             if (cmd.length()==350){
                String f = cmd.substring(8,11);
                String g = cmd.substring(12,15);
                String h = cmd.substring(16,17);
                String i = cmd.substring(18,21);
            
                a1=f.toInt();
                b1=g.toInt();
                c1=h.toInt();
                d1=i.toInt();
                
                Serial.print("New IP: " + String(a1) + ".");
                Serial.print(String(b1)+".");
                Serial.print(String(c1)+".");
                Serial.print(String(d1)+"\n");
                
                EEPROM.write(IPa, a1);
                EEPROM.write(IPb, b1);
                EEPROM.write(IPc, c1);
                EEPROM.write(IPd, d1);
                delay(1000);
                result=f+"."+g+"."+h+"."+i;
                
               }
              else result="Syntax Error";
            }

              else if (cmd.substring(5,7) =="95") {
               digitalWrite(Led_Lan, LOW);
               delay(100);
               digitalWrite(Led_Lan, HIGH);
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
            
            client.println("HTTP/1.1 200 OK");
            client.println("Content-Type: text/html");
            client.println(""); //  do not forget this one
            client.println("<!DOCTYPE HTML>");
            client.println("<html>");
            client.println("<head>");
            client.println("<meta charset='utf-8'>");
            client.println("<meta name='viewport' content='width=device-width, initial-scale=1'>");
            client.println("<meta http-equiv='x-ua-compatible' content='ie=edge'>");
            client.println("<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-alpha.6/css/bootstrap.min.css' integrity='sha384-rwoIResjU2yc3z8GV/NPeZWAv56rSmLldC3R/AZzGRnGxQQKnKkoFVhFQhNUwEyJ' crossorigin='anonymous'>");  
            client.println("</head>");
            client.println("<center>");
            client.println("<body>"); 
            client.println("<br><br>");
            client.println("<div class='col-md-6'>");
            client.println("<div class = 'container-fluid'>");
            client.println("<div class ='row'>"); 
            client.println("<div class ='col-md-6'>");
            client.println("<div class='card mb-3'>");
            client.println("<div class = 'card-header'>");
            client.println("<p>Sistem Pajak Online<p>");
            client.println("<p>===================<p>");
            client.println("Jam : "+gettime);
            client.println("<p> <p>");
            client.println("Nomor Porporasi : "+eporporasi);
            client.println("<p> <p>");
            client.println("Notifikasi : "+result);
            client.println("<p> <p>");
            client.println("Status Jaringan : " + Status);
            client.println("<p> <p>");
            client.println("<p>Note : Gunakan IP Kelas C 192.168.1.(100-177) <p>");
            client.println("</div>");
            client.println("</div>");
            client.println("</div>");
            client.println("</div>");
            client.println("</div>");
            client.println("</div>");
            client.println("</body>");
            client.println("</center>");
            client.println("</html>"); //Akhir script HTML
            client.println("</html>");
            break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;

        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;

        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    cmd="";
    eporporasi="";
    gsm_result="";
    result="";
    Serial.println("client disconnected");
  }
}

void gsm_sendhttp() {

  char Kirim_ID;
      for (int y=0; y<=6 ; y++){
       Kirim_ID = EEPROM.read(Simpan_ID+y);
      }
  
  Serial1.println("AT");
  AT_respon();//Print GSM Status an the Serial Output;
  delay(4000);
  Serial1.println("AT+SAPBR=3,1,Contype,GPRS");
  AT_respon();
  delay(100);
  Serial1.println("AT+SAPBR=3,1,APN," + apn);
  AT_respon();
  delay(100);
  //  Serial1.println("AT+SAPBR=3,1,USER," + apn_u); //Comment out, if you need username
  AT_respon();
  delay(100);
  //  Serial1.println("AT+SAPBR=3,1,PWD," + apn_p); //Comment out, if you need password
  AT_respon();
  delay(100);
  Serial1.println("AT+SAPBR =1,1");
  AT_respon();
  delay(100);
  Serial1.println("AT+SAPBR=2,1");
  AT_respon();
  delay(2000);
  Serial1.println("AT+HTTPINIT");
  AT_respon();
  delay(100);
  Serial1.println("AT+HTTPPARA=CID,1");
  AT_respon();
  delay(100);
  Serial1.println("AT+HTTPPARA=URL," + url + "porporasi=" + eporporasi + "&devid=" + String(Kirim_ID)  + "&total=" + Rp + "&date=" + tgl +"&time=" + jam);
  AT_respon();
  delay(100);
  Serial1.println("AT+HTTPPARA=CONTENT,application/x-www-form-urlencoded");
  AT_respon();
  delay(100);
  Serial1.println("AT+HTTPDATA=192,10000");
  AT_respon();
  delay(10000);
  Serial1.println("AT+HTTPACTION=1");
  AT_respon();
  delay(5000);
  Serial1.println("AT+HTTPREAD");
  AT_respon();
  delay(100);
  Serial1.println("AT+HTTPTERM");
  AT_respon();
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


void AT_respon() {
  while (Serial1.available()) {
    char gsm = Serial1.read();
    Serial.write(gsm);
    gsm_result += gsm;
  }
  Serial.println(gsm_result.length());
  if (gsm_result.length() == 44){
    Status = "Tidak ada koneksi!";
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
