#ifndef _SEQUENCE_CONTROLS_H_
#define _SEQUENCE_CONTROLS_H_

#include <lcdgfx.h>
#include <uClock.h>
#include "Control.h"
#include "SequencerInput.h"

class SequenceControlBPM: public Control
{
public:
    SequenceControlBPM(int xPos, int yPos, DisplaySSD1327_128x128_I2C* display) : Control(xPos, yPos, display) {
        this->w = 40;
        this->h = 18;
    }
    
    void draw() {
        
        float tempo = uClock.getTempo();
        char s[4];
        snprintf(s, 4, "%f", tempo);
        Serial.println(s);

        printFixed(0, 0, "BPM");
        printFixed(0, 10, s);
    }

    void onEncoderChange(int increments) {
        float tempo = uClock.getTempo() + increments;
        uClock.setTempo(tempo);
    }
};


class PositionControl: public Control
{
public:
    PositionControl(int xPos, int yPos, DisplaySSD1327_128x128_I2C* display, SequencerInput* seqInput) : Control(xPos, yPos, display) {
        this->seqInput = seqInput;
        this->w = 40;
        this->h = 18;
    }

    void draw() {
        int step_pos = this->seqInput->getStepPosition();
        char s[5];
        snprintf(s, 5, "%d-%02d", step_pos + 1, step_pos + 8);
        printFixed(0, 0, "Pos");
        printFixed(0, 10, s);
    }

    void onEncoderChange(int increments) {
        this->seqInput->moveBy(increments);
    }
protected:
    SequencerInput* seqInput;
};

#endif