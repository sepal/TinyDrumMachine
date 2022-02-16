#ifndef _SEQUENCER_PAGE_H_
#define _SEQUENCER_PAGE_H_

#include "SequenceControls.h"

#include <Arduino.h>
#include "Pages.h"
#include "SequenceControls.h"

class SequencerPage : public Page
{
public:
    SequencerPage(DisplaySSD1327_128x128_I2C *display, SequencerInput *seqInput);

    virtual const char* getTitle();

    virtual Control* getControl(uint8_t x, uint8_t y);

    virtual uint8_t width();
    virtual uint8_t height();

protected:
    Control *controls[1][2];
};

#endif