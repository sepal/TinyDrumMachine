#ifndef _SEQUENCE_CONTROLS_H_
#define _SEQUENCE_CONTROLS_H_

#include <lcdgfx.h>
#include <uClock.h>
#include "Control.h"

class SequenceControlBPM: public Control
{
public:
    SequenceControlBPM(int xPos, int yPos, DisplaySSD1327_128x128_I2C* display) : Control(xPos, yPos, display) {}
    
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

#endif