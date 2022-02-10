#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int buttonPin = 2;

boolean buttonIsPressed = false;

void setup()
{
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonPressed, FALLING);

  lcd.init();
  lcd.backlight();
  delay(300);
}

void loop()
{
  if (buttonIsPressed) {
    buttonIsPressed = false;
    lcd.setCursor(0,0);
    lcd.print("Hello, world!");
    delay(1000);
    lcd.clear();
  }
}

void buttonPressed() {
  buttonIsPressed = true;
}
