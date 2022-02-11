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
        this->w = 39;
        this->h = 34;
    }
    
    void draw() {
        
        float tempo = uClock.getTempo();
        char s[4];
        snprintf(s, 4, "%f", tempo);
        Serial.println(s);

        printFixed(0, 0, "BPM\n");
        printFixed(0, 16, s);
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
        this->w = 104;
        this->h = 34;
    }

    void draw() {
        int step_pos = this->seqInput->getStepPosition();
        char s[9];
        snprintf(s, 9, "< %d-%02d >", step_pos + 1, step_pos + 8);
        printFixed(0, 0, "Position");
        printFixed(0, 16, s);
    }

    void onEncoderChange(int increments) {
        this->seqInput->moveBy(increments);
    }
protected:
    SequencerInput* seqInput;
};

#endif