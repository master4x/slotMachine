/*
 * FloppySlotSound.cpp - Library for playing sound for our slotmachine with a floppydrive.
 * Created by Maximilian Wotsch, February 22, 2022.
*/
#include "Arduino.h"
#include "FloppySlotSound.h"
#include <MusicFloppy.h>

FloppySlotSound::FloppySlotSound(int driveSelectPin, int directionPin, int stepPin) {
    myDrive.setDriveSelectPin(driveSelectPin);
    myDrive.setDirectionPin(directionPin);
    myDrive.setStepPin(stepPin);
}

void FloppySlotSound::playTone(int frequency, unsigned long durationTime) {
    myDrive.playTone(frequency, durationTime);
}

void FloppySlotSound::startSound() {
    myDrive.playTone(100,500);
    myDrive.playTone(150,500);
    myDrive.playTone(200,250);
}

void FloppySlotSound::smallWin() {
    int toneDuration = 300;
    for (int i = 0; i < 2; i++) {
        for (int i = 0; i < 2; i++) {
            myDrive.playTone(100+50*i, toneDuration);
        }
    }
    
}

void FloppySlotSound::mediumWin() {
    int toneDuration = 250;
    for (int i = 0; i < 2; i++) {
        for (int i = 0; i < 3; i++) {
            myDrive.playTone(100+50*i, toneDuration);
        }
        for (int i = 0; i < 3; i++) {
            myDrive.playTone(250-50*i, toneDuration);
        }
    }
}

void FloppySlotSound::bigWin() {
    int toneDuration = 250;
    for (int i = 0; i < 3; i++) {
        for (int i = 0; i < 5; i++) {
            myDrive.playTone(100+50*i, toneDuration);
        }
        for (int i = 0; i < 3; i++) {
            myDrive.playTone(350-50*i, toneDuration);
        }
    }
}