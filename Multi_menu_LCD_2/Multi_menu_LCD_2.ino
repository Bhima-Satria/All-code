#include <LiquidCrystal.h>
#include <SoftwareSerial.h>


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int currentMenuItem = 0;
int lastState = 0;
int up = A1;
int down = A2;
int left = A3;
int right = A4;
int enter = A5;

void setup() {
  pinMode(up, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);
  pinMode(left, INPUT_PULLUP);
  pinMode(right, INPUT_PULLUP);
  pinMode(enter, INPUT_PULLUP);
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Tutor bagus");
  lcd.setCursor(0,1);
  lcd.print("membuat Menu");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" Menu 1");
  lcd.setCursor(0,1);
  lcd.print(" Menu 2");
}

void loop() {
  mainmenu();
}

void mainmenu(){
  int state = 0;
  if (digitalRead(up) == LOW){
    state = 1; 
  }
  else if(digitalRead(down) == LOW){
    state = 2;
  }
  else if(digitalRead(enter) == LOW){
    state = 3;
  }
//  if (currentMenuItem &lt; 0 || currentMenuItem &gt; 4){
//    currentMenuItem = 0;
//  }
  if (state != lastState) {
    if (state ==1 ){
      currentMenuItem = currentMenuItem - 1;
      displayMenu(currentMenuItem);
    }
    else if (state == 2){
      currentMenuItem = currentMenuItem + 1;
      displayMenu(currentMenuItem);
    }
    else if (state == 3){
      selectMenu(currentMenuItem);
    }
    lastState = state;
  }
  delay(5);
}

void displayMenu(int x){
  switch(x){
    case 1:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.write(char(220));
      lcd.print(" Menu 1");
      lcd.setCursor(0,1);
      lcd.print(" Menu 2");
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(" Menu 1");
      lcd.setCursor(0,1);
      lcd.write(char(220));
      lcd.print(" Menu 2");
      break;
    case 3:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.write(char(220));
      lcd.print(" Menu 3");
      lcd.setCursor(0,1);
      lcd.print(" Menu 4");
      break;
    case 4:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(" Menu 3");
      lcd.setCursor(0,1);
      lcd.write(char(220));
      lcd.print(" Menu 4");
      break;
  }
}

void selectMenu(int x){
  switch(x){
    case 1:
      lcd.clear();
      lcd.print("menu 1 Dipilih");
      break;
    case 2:
      lcd.clear();
      lcd.print("menu 2 Dipilih");
      break;
    case 3:
      lcd.clear();
      lcd.print("menu 3 Dipilih");
      break;
    case 4:
      lcd.clear();
      lcd.print("menu 4 Dipilih");
      break;
  }
}
