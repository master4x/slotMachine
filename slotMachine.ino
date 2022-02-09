#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int buttonPin = 2;

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
  
}

void buttonPressed() {
  lcd.setCursor(0,0);
  lcd.print("Hello, world!");
  delay(1000);
  lcd.clear();
}
