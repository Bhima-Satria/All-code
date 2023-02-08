#include <SoftwareSerial.h>

SoftwareSerial SIM800(2, 3); // RX | TX
// Connect the SIM800L TX to Arduino pin 2 RX. 
// Connect the SIM800L RX to Arduino pin 3 TX. 

float suhu=24.6;
float kelembaban=90;
float MoM=5;

void setup() 
{
    // start th serial communication with the host computer
    Serial.begin(9600);
    while(!Serial);
    Serial.println("Arduino with SIM is ready");
    
    SIM800.begin(9600);  
    Serial.println("SIM started at 9600");
    delay(1000);
    Serial.println("Setup Complete! SIM is Ready!");
}

void loop() {
  kirimData();

}

void ShowSerialData()
{
  while(SIM800.available()!=0)
    Serial.write(char (SIM800.read()));
}

void kirimData()
{
  SIM800.println("AT+CSQ"); // Mengecek Kualitas Sinyal
  ShowSerialData();

  SIM800.println("AT+CGATT?"); //Melihat Support tidaknya GPRS
  delay(100);
  ShowSerialData();

  SIM800.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  delay(1000);
  ShowSerialData();

  SIM800.println("AT+CIPSTATUS");
  delay(3000);
  ShowSerialData();

  SIM800.println("AT+SAPBR=3,1,\"APN\",\"internet\"");
  delay(3000);
  ShowSerialData();

  SIM800.println("AT+SAPBR=1,1");
  delay(20000);
  ShowSerialData();

  SIM800.println("AT+HTTPINIT"); //Persiapan HTTP request
  delay(1000); 
  ShowSerialData();

  //pengiriman data ke alamat URL web server
  SIM800.print("AT+HTTPPARA=\"URL\",\"http://ulindev.com/project/tes/dataku.php?nilai=");
  delay(100);
  SIM800.println(random(0,100));
  delay(2000);
  ShowSerialData();

  SIM800.println("AT+HTTPACTION=0"); //submit request 
  delay(5000);
  ShowSerialData();

  SIM800.println("");
  delay(100);

  SIM800.println("AT+HTTPREAD");//baca data dari website yang diakses
  delay(300);
  ShowSerialData();
}
