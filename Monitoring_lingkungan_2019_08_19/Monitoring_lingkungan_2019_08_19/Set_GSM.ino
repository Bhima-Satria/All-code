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
  Serial.println("Kirim ftp");
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
  //Power
  cmd4 += "/e/";
  cmd4 += String(Energy);
  cmd4 += '"';
  cmd4 += "\r\n\r\n";
  //

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
