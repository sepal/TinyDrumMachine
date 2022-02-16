#ifndef _SEQUENCE_CONTROLS_H_
#define _SEQUENCE_CONTROLS_H_

#include <lcdgfx.h>
#include <uClock.h>
#include "Control.h"
#include "SequencerInput.h"

class SequenceControlBPM : public Control
{
public:
    SequenceControlBPM(int xPos, int yPos, DisplaySSD1327_128x128_I2C *display);

    void draw();
    void onEncoderChange(int increments);
};

class PositionControl : public Control
{
public:
    PositionControl(int xPos, int yPos, DisplaySSD1327_128x128_I2C *display, SequencerInput *seqInput);

    void draw();
    void onEncoderChange(int increments);

protected:
    SequencerInput *seqInput;
};

#endif