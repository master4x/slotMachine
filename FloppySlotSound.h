/*
 * FloppySlotSound.h - Library for playing sound for our slotmachine with a floppydrive.
 * Created by Maximilian Wotsch, February 22, 2022.
*/
#ifndef FloppySlotSound_h
#define FloppySlotSound_h

#include "Arduino.h"
#include <MusicFloppy.h>

class FloppySlotSound
{
private:
    MusicFloppy myDrive;
public:
    FloppySlotSound(int driveselectPin, int directionPin, int stepPin);
    void playTone(int frequency, unsigned long durationTime);
    void startSound();
};

#endif