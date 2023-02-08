#include <LiquidCrystal_I2C.h> //Header file for LCD from https://www.arduino.cc/en/Reference/LiquidCrystal
#include <Keypad.h> //Header file for Keypad from https://github.com/Chris--A/Keypad
#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>   // The following files are included in the libraries Installed
#include <NfcAdapter.h>

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Three columns

// Define the Keymap
char keys[ROWS][COLS] = {

  {'1', '2', '3', 'A'},

  {'4', '5', '6', 'B'},

  {'7', '8', '9', 'C'},

  {'*', '0', '#', 'D'}

};

byte rowPins[ROWS] = { 3, 5, 7, 9 };// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte colPins[COLS] = { 11, 13, 15, 17 }; // Connect keypad COL0, COL1 and COL2 to these Arduino pins.

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); //  Create the Keypad

LiquidCrystal_I2C lcd(0x3F, 16, 2);

long int Num1, Num2, Number;
char key, action;
boolean result = false;
String payloadAsString = "";

void setup() {
  Serial.begin(9600);
  Wire.begin();
  lcd.begin(); //We are using a 16*2 LCD display

  delay(2000); //Wait for display to show info
  lcd.clear(); //Then clean it

  nfc.begin();
}

void loop() {
  key = kpd.getKey(); //storing pressed key value in a char
  menu();
}

void DetectButtons()
{
  lcd.clear(); //Then clean it
  if (key == '*') //If cancel Button is pressed
  {
    Serial.println ("Button Cancel");
    Number = Num1 = Num2 = 0;
    result = false;
  }

  if (key == '1') //If Button 1 is pressed
  { Serial.println ("Button 1");
    if (Number == 0)
      Number = 1;
    else
      Number = (Number * 10) + 1; //Pressed twice
  }

  if (key == '4') //If Button 4 is pressed
  { Serial.println ("Button 4");
    if (Number == 0)
      Number = 4;
    else
      Number = (Number * 10) + 4; //Pressed twice
  }

  if (key == '7') //If Button 7 is pressed
  { Serial.println ("Button 7");
    if (Number == 0)
      Number = 7;
    else
      Number = (Number * 10) + 7; //Pressed twice
  }


  if (key == '0')
  { Serial.println ("Button 0"); //Button 0 is Pressed
    if (Number == 0)
      Number = 0;
    else
      Number = (Number * 10) + 0; //Pressed twice
  }

  if (key == '2') //Button 2 is Pressed
  { Serial.println ("Button 2");
    if (Number == 0)
      Number = 2;
    else
      Number = (Number * 10) + 2; //Pressed twice
  }

  if (key == '5')
  { Serial.println ("Button 5");
    if (Number == 0)
      Number = 5;
    else
      Number = (Number * 10) + 5; //Pressed twice
  }

  if (key == '8')
  { Serial.println ("Button 8");
    if (Number == 0)
      Number = 8;
    else
      Number = (Number * 10) + 8; //Pressed twice
  }


  if (key == '#')
  { Serial.println ("Button Equal");
    Num2 = Number;
    result = true;
  }

  if (key == '3')
  { Serial.println ("Button 3");
    if (Number == 0)
      Number = 3;
    else
      Number = (Number * 10) + 3; //Pressed twice
  }

  if (key == '6')
  { Serial.println ("Button 6");
    if (Number == 0)
      Number = 6;
    else
      Number = (Number * 10) + 6; //Pressed twice
  }

  if (key == '9')
  { Serial.println ("Button 9");
    if (Number == 0)
      Number = 9;
    else
      Number = (Number * 10) + 9; //Pressed twice
  }

  if (key == 'A' || key == 'B' || key == 'C' || key == 'D') //Detecting Buttons on Column 4
  {
    Num1 = Number;
    Number = 0;
    if (key == 'C')
    {
      Serial.println ("Multiplication");
      action = '+';
    }
    if (key == 'D')
    {
      Serial.println ("Devesion");
      action = '-';
    }

    delay(100);
  }

}

void CalculateResult()
{
  if (action == '+')
    Number = Num1 + Num2;

  if (action == '-')
    Number = Num1 - Num2;

  if (action == '*')
    Number = Num1 * Num2;

  if (action == '/')
    Number = Num1 / Num2;
}

void DisplayResult()
{

  lcd.setCursor(0, 0);   // set the cursor to column 0, line 1
  lcd.print(Num1); lcd.print(action); lcd.print(Num2);

  if (result == true)
  {
    lcd.print(" =");  //Display the result
    lcd.print(Number);
  }

  lcd.setCursor(0, 1);   // set the cursor to column 0, line 1
  lcd.print(Number); //Display the result
}

void menu() {

Menu:
  while (1) {
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Litro-EDC");
    lcd.setCursor(0, 1);
    lcd.print("1.Paid");
    lcd.setCursor(8, 1);
    lcd.print("3.E-Cash");
    delay(100);
    key = kpd.getKey();
    if (key == 'A') {
      delay(100);
      goto Menu;
    }
    if (key == '1') {
      delay(100);
      goto Paid;
    }
    if (key == '3') {
      delay(100);
      goto Ecash;
    }
    if (key == 'D') {
      delay(100);
      goto Menu2;
    }
  }

Paid:
  while (1) {
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Pembayaran");
    lcd.setCursor(0, 1);
    lcd.print("Call");
    lcd.setCursor(11, 1);
    lcd.print("Close");
    delay(100);
    key = kpd.getKey();
    if (key == 'A') {
      delay(100);
      goto Menu;
    }
    if (key == 'B') {
      delay(100);
      goto Menu;
    }
    if (key == 'D') {
      delay(100);
      lcd.clear();
      goto pay ;
    }
  }

pay:
  while (1) {
    key = kpd.getKey();
    if (key != NO_KEY)
      DetectButtons();

    if (result == true)
      result = true;
    Displaytopup();
    int bayar = 0;
    String nilai = String(Num1);

    if (key == 'D')
    {
      lcd.clear();
      if (nfc.tagPresent())
      {
        NfcTag tag = nfc.read();
        if (tag.hasNdefMessage()) // If your tag has a message
        {
          NdefMessage message = tag.getNdefMessage();
          NdefRecord record = message.getRecord(1);
          int payloadLength = record.getPayloadLength();
          byte payload[payloadLength];
          record.getPayload(payload);
          String payloadAsString = ""; // Processes the message as a string vs as a HEX value
          for (int c = 0; c < payloadLength; c++) {
            payloadAsString += (char)payload[c];
          }
          bayar = payloadAsString.substring(1).toInt() - Num1;
          if (bayar < 0) {
            nilai = payloadAsString.substring(1);
            lcd.setCursor(0, 0);
            lcd.print("Saldo Kurang..");
            delay(2000);
            goto Menu;
          } else {
            nilai = String(bayar);
            lcd.setCursor(0, 0);
            lcd.print("Processing..");
            delay(2000);
          }
        }

        NdefMessage message = NdefMessage();
        message.addTextRecord("");
        message.addUriRecord(nilai);
        message.addTextRecord("");
        boolean success = nfc.write(message);
        if (success) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Succes.."); // if it works you will see this message
          delay(3000);
          Num1 = 0;
          goto ceksaldo;
        } else {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Failed..");
          delay(3000);
          Num1 = 0;
          goto Menu;
        }
      }
    }

    if (key == 'A')
    {
      Serial.println ("Menu1");
      goto Menu;
    }
  }

Ecash:
  while (1) {
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("E-Cash");
    lcd.setCursor(0, 1);
    lcd.print("1.Saldo");
    lcd.setCursor(8, 1);
    lcd.print("3.Top-Up");
    delay(100);
    key = kpd.getKey();
    if (key == 'A') {
      delay(100);
      goto Menu;
    }
    if (key == '1') {
      delay(100);
      goto ceksaldo;
    }
    if (key == '3') {
      delay(100);
      lcd.clear();
      goto topup;
    }
  }

ceksaldo:
  while (1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Saldo Anda :");

    if (nfc.tagPresent())
    {
      NfcTag tag = nfc.read();

      if (tag.hasNdefMessage()) // If your tag has a message
      {
        NdefMessage message = tag.getNdefMessage();
        NdefRecord record = message.getRecord(1);
        int payloadLength = record.getPayloadLength();
        byte payload[payloadLength];
        record.getPayload(payload);
        String payloadAsString = ""; // Processes the message as a string vs as a HEX value
        for (int c = 0; c < payloadLength; c++) {
          payloadAsString += (char)payload[c];
        }
        lcd.setCursor(0, 0);
        lcd.print("Saldo Anda : ");
        lcd.setCursor(0, 1);
        lcd.print("Rp : ");
        lcd.setCursor(5, 1);
        lcd.print(payloadAsString.substring(1));
        delay(3000);
        goto Menu;
      }
    }
  }

topup:
  while (1) {
    key = kpd.getKey();
    if (key != NO_KEY)
      DetectButtons();

    if (result == true)
      result = true;
    Displaytopup();
    String nilai = String(Num1);

    if (key == 'D')
    {
      if (nfc.tagPresent()) {
        NdefMessage message = NdefMessage();
        message.addTextRecord("");
        message.addUriRecord(nilai);
        message.addTextRecord("");
        boolean success = nfc.write(message);
        if (success) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Top-Up Succes"); // if it works you will see this message
          delay(3000);
          goto ceksaldo;
          Num1 = 0;
        } else {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Top-Up Failed"); // If the the rewrite failed you will see this message
          delay(3000);
          goto topup;
          Num1 = 0;
        }
      }
    }

    if (key == 'A')
    {
      Serial.println ("Menu1");
      goto Menu;
    }
    if (key == 'B')
    {
      Serial.println ("Menu2");
      goto Menu2;
    }
  }

Menu2:
  while (1) {
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Litro-EDC");
    lcd.setCursor(0, 1);
    lcd.print("4.Kalkulator");
    delay(100);
    key = kpd.getKey();
    if (key == 'A') {
      delay(100);
      goto Menu;
    }
    if (key == '4') {
      delay(100);
      lcd.clear();
      goto kalkulator;
    }
  }

kalkulator:
  while (1) {
    key = kpd.getKey();
    if (key != NO_KEY)
      DetectButtons();

    if (result == true)
      CalculateResult();
    DisplayResult();

    if (key == 'A')
    {
      Serial.println ("Menu1");
      goto Menu;
    }
    if (key == 'B')
    {
      Serial.println ("Menu2");
      goto Menu2;
    }
  }
}

void Displaytopup()
{

  lcd.setCursor(0, 0);   // set the cursor to column 0, line 1
  lcd.print("Masukan Nominal");
  lcd.setCursor(0, 1);
  lcd.print("Rp : ");
  lcd.setCursor(5, 1);// set the cursor to column 0, line 1
  lcd.print(Number); //Display the result
}
