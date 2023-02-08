/*****************************************
 *  Program 1 : Tes Koneksi
 *  Serial1 V2
 *  www.inkubator-teknologi.com
 *  www.tokotronik.com
 *****************************************/
 
#include <SoftwareSerial.h>
SoftwareSerial Serial1(8, 9); // RX, TX

#include <LiquidCrystal.h>

String inString="";
char str,f,c;
//============================
void getmodem()
{ 
 f=1; 
 while(f)
 {
   if(Serial1.available())     
     {
       str=Serial1.read(); 
       Serial.print(str);         
       switch (str)
         {
           case '\r': break;
           case '\n':f=0; break;
           default:inString+=(char)str;
         }        
     }
 }
} 
//===================================
// AT+UART_DEF=9600,8,1,0,0
void setup() { 
  Serial.begin(9600);
  Serial1.begin(115200);  
  //Serial1.begin(9600);  
  Serial1.println("AT+UART_DEF=9600,8,1,0,0");
  delay(1000);
}

void loop() {
 if (Serial1.available()){
  c=Serial1.read();
  Serial.write(c);
 }
 if(Serial.available()){
  c=Serial.read();
  Serial1.write(c);
 }
}
