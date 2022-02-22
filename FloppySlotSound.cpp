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
    myDrive.playTone(100,250);
    myDrive.playTone(150,250);
    myDrive.playTone(200,250);
}

void FloppySlotSound::smallWin() {
}

void FloppySlotSound::mediumWin() {
}

void FloppySlotSound::bigWin() {
}