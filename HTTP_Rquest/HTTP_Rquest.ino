void setup() {
  
 Serial.begin(9600);
 Serial1.begin(9600);
 
  Serial.println("Initializing...");
  delay(1000);

  kirimData();
  
}

void loop() {
  
}

void ShowSerialData()
{
  while(Serial1.available()!=0)
    Serial.write(char (Serial1.read()));
}

void kirimData()
{
  Serial1.println("AT+CSQ"); // Mengecek Kualitas Sinyal
  ShowSerialData();
  delay(1000);

  Serial1.println("AT+CGATT?"); //Melihat Support tidaknya GPRS
  delay(1000);
  ShowSerialData();

  Serial1.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  delay(1000);
  ShowSerialData();

  Serial1.println("AT+SAPBR=3,1,\"APN\",\"axis\"");
  delay(1000);
  ShowSerialData();

  Serial1.println("AT+SAPBR=1,1");
  delay(10000);
  ShowSerialData();

  Serial1.println("AT+HTTPINIT"); //Persiapan HTTP request
  delay(1000); 
  ShowSerialData();

  //pengiriman data ke alamat URL web server
  Serial1.print("AT+HTTPPARA=\"URL\",\"http://ulindev.com/project/tes/dataku.php?nilai=");
  Serial1.print(random(0,100));
  delay(2000);
  ShowSerialData();

  Serial1.println("AT+HTTPACTION=0"); //submit request 
  delay(5000);
  ShowSerialData();

  Serial1.println("");
  delay(100);

  Serial1.println("AT+HTTPTERM");//baca data dari website yang diakses
  delay(300);
  ShowSerialData();
}
