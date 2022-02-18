#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int buttonPin = 2;
const unsigned long interval = 3000;
const int turnDisplayDelay = 750;

boolean buttonIsPressed = false;
unsigned long previousMillis = 0, currentMillis = 0;
int slot[4];
int score = 100;

void setup()
{
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonPressed, FALLING);

  lcd.init();
  lcd.backlight();
  delay(300);
  generateField();
  displayScore();
}

void loop()
{
  if (buttonIsPressed) {
    turn();
    buttonIsPressed = false;
  }
}

void buttonPressed() {
  currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    buttonIsPressed = true;
  }
}

void generateField() {
  lcd.setCursor(1,0);
  lcd.print("|");
  lcd.setCursor(3,0);
  lcd.print("|");
  lcd.setCursor(5,0);
  lcd.print("|");
  lcd.setCursor(11,0);
  lcd.print("Score");
}

void turn() {
  if(turnAllowed()) {
    generateSlot();
    displayScore();
    displayTurn();
    calculeteScore();
    displayScore();
  }
}

bool turnAllowed() {
  if (score <= 0) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Score to low :-(");
    lcd.setCursor(1,1);
    lcd.print("bit.ly/3sNgXRx");
    return false;
  }
  return true;
}

void generateSlot() {
  score--;
  for (int i = 0; i < 4; i++) {
    slot[i] = random(0,9);
  }
}

void displayTurn() {
  lcd.setCursor(0,0);
  lcd.print(" | | ");
  int i = 0;
  for (int j = 0; j < 7; j = j+2) {
    delay(turnDisplayDelay);
    lcd.setCursor(j,0);
    lcd.print(slot[i]);
    i++;
  }
}

void calculeteScore() {
  /* 4 simmelar */
  if      (  slot[0] == slot[1] && slot[0] == slot[2] && slot[0] == slot[3] )
    score += 100;
  /* 3 simmelar */
  else if ( slot[0] == slot[1] && slot[0] == slot[2] ||
            slot[0] == slot[1] && slot[0] == slot[3] ||
            slot[0] == slot[2] && slot[0] == slot[3] ||
            slot[1] == slot[2] && slot[1] == slot[3]    )
    score += 25;
  /* 2 simmelar */
  else if ( slot[0] == slot[1] ||
            slot[0] == slot[2] ||
            slot[0] == slot[3] ||
            slot[1] == slot[2] ||
            slot[1] == slot[3] ||
            slot[2] == slot[3]    )
    score += 1;
}

int neededDigits(int value) {
  int digits = 0;
  if (value == 0)
    return 1;
  while (value > 0) {
    value /= 10;
    digits++;
  }
  return digits;
}
void displayScore() {
  lcd.setCursor(12,1);
  lcd.print("   ");
  lcd.setCursor(16-neededDigits(score),1);
  lcd.print(score);
}
