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
    lcd.print(Power);
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
    lcd.print(humread()); 
    //lcd.print("10");
    lcd.print("%");
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
    pilih_awal(3);
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
    //lcd.setCursor(2, 0);
    //lcd.print("Tegangan");
    pilih_awal(3);
    //Serial.print("nilai tombol =");
    //Serial.println(tombol);
    if (tombol < 4)
    {
      lcd.setCursor(1, 0);
      lcd.print("1.Current= "); lcd.print(Current); lcd.print(" mA");
      lcd.setCursor(1, 1);
      lcd.print("1.Voltage= "); lcd.print(Voltage); lcd.print(" V");
      lcd.setCursor(1, 2);
      lcd.print("2.Power  = "); lcd.print(Power); lcd.print(" mW");
      lcd.setCursor(1, 3);
      lcd.print("3.Energy = "); lcd.print(Energy); lcd.print(" mWh");
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
    pilih_awal(3);
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
    pilih_awal(3);
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
    pilih_awal(3);
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
    pilih_awal(3);
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
    pilih_awal(3);
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
    pilih_awal(3);
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
