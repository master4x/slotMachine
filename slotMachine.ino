#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int buttonPin = 2;

boolean buttonIsPressed = false;
int slot[3];
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
  buttonIsPressed = true;
}

void generateField() {
  lcd.setCursor(1,0);
  lcd.print("|");
  lcd.setCursor(3,0);
  lcd.print("|");
  lcd.setCursor(11,0);
  lcd.print("Score");
}

void turn() {
  if(turnAllowed()) {
    generateSlot();
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
    return false;
  }
  return true;
}

void generateSlot() {
  score--;
  for (int i = 0; i < 3; i++) {
    slot[i] = random(0,9);
  }
}

void displayTurn() {
  int i = 0;
  for (int j = 0; j < 5; j = j+2) {
    lcd.setCursor(j,0);
    lcd.print(slot[i]);
    i++;
  }
}

void calculeteScore() {
  /* code */
}

void displayScore() {
  lcd.setCursor(13,1);
  lcd.print(score);
}
