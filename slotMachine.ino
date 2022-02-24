/**
 * @file    slotMachine.ino
 * @author  Maximilian Wotsch, Leon Niklas Kelle
 * @brief   code for our self build slotmachine powerd by an arduino
 * @version 0.1
 * @date    2022-02-09
 * 
 * @copyright Copyright (c) 2022
 */
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "FloppySlotSound.h" // selfwritten header-file for the sound of our slotmachine

LiquidCrystal_I2C lcd(0x27, 16, 2);
FloppySlotSound   myDrive(3,4,5);

const int buttonPin = 2;
const unsigned long interval = 3000;
const int turnDisplayDelay = 750;

boolean buttonIsPressed = false;
unsigned long previousMillis = 0, currentMillis = 0;
int slot[4];
int score = 100;

/**
 * @brief setup function
 * 
 * initilize LCD and pushbutton and sets a randomSeed() for the random function so it generates diffrent values after restart
 */
void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonPressed, FALLING);
  randomSeed(analogRead(0));

  lcd.init();
  lcd.backlight();
  delay(300);
  generateField();
  myDrive.startSound();
  displayScore();
}

/**
 * @brief loop-function
 * 
 * triggers the turn() routine if buttonIsPressed is set true by the interrupt
 * afer turn() routine buttonIsPressed gets reseted
 */
void loop() {
  if (buttonIsPressed) {
    turn();
    buttonIsPressed = false;
  }
}

/**
 * @brief gets triggerd by the interrupt
 * 
 * debounces button and sets vriable buttonIsPressed to true
 */
void buttonPressed() {
  currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    buttonIsPressed = true;
  }
}

/**
 * @brief function for the generation of the game field in the setup
 */
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

/**
 * @brief turn routine wich gets triggerd if the button was pressed
 * 
 * if a turn is allowd it runs through the steps of a turn
 */
void turn() {
  if(turnAllowed()) {
    generateSlot();
    displayScore();
    displayTurn();
    calculeteScore();
    displayScore();
  }
}

/**
 * @brief validates if the score is to low
 * 
 * if the score is to low it will be displayed by the LCD and the user is not allowed to turn
 * 
 * @return true  turn is valid
 * @return false score is to low
 */
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

/**
 * @brief generates 4 random digits for the 4 slots
 */
void generateSlot() {
  score--;
  for (int i = 0; i < 4; i++) {
    slot[i] = random(0,9);
  }
}

/**
 * @brief displays the new generated turn on the LCD
 */
void displayTurn() {
  lcd.setCursor(0,0);
  lcd.print(" | | | ");
  int i = 0;
  for (int j = 0; j < 7; j = j+2) {
    delay(turnDisplayDelay);
    lcd.setCursor(j,0);
    myDrive.playTone(75,250);
    lcd.print(slot[i]);
    i++;
  }
}

/**
 * @brief calculates the amount of winned points
 * 
 */
void calculeteScore() {
  /* 4 simmelar */
  if      (  slot[0] == slot[1] && slot[0] == slot[2] && slot[0] == slot[3] ) {
    score += 50;
    displayScore();
    myDrive.bigWin();
  }
  /* 3 simmelar */
  else if ( slot[0] == slot[1] && slot[0] == slot[2] ||
            slot[0] == slot[1] && slot[0] == slot[3] ||
            slot[0] == slot[2] && slot[0] == slot[3] ||
            slot[1] == slot[2] && slot[1] == slot[3]    ) {
    score += 5;
    displayScore();
    myDrive.mediumWin();
   }
  /* 2 simmelar */
  else if ( slot[0] == slot[1] ||
            slot[0] == slot[2] ||
            slot[0] == slot[3] ||
            slot[1] == slot[2] ||
            slot[1] == slot[3] ||
            slot[2] == slot[3]    ) {
    score += 1;
    displayScore();
    myDrive.smallWin();
  }
}

/**
 * @brief calculets the amount of needed digits for the score
 * 
 * @param value value from which the amount of digits is needed
 * @return int  amount of neded digits
 */
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

/**
 * @brief displays score on the LCD
 * 
 * score is disolayed on the bottom right corner of the LCD
 */
void displayScore() {
  lcd.setCursor(12,1);
  lcd.print("   ");
  lcd.setCursor(16-neededDigits(score),1);
  lcd.print(score);
}
