#ifndef _SEQUENCER_PAGE_H_
#define _SEQUENCER_PAGE_H_

#include "SequenceControls.h"

#include <Arduino.h>
#include "TextPage.h"
#include "SequenceControls.h"

class SequencerPage : public TextPage
{
public:
    SequencerPage(DisplaySSD1351_128x128x16_SPI* display, EncoderInput* encoder, FiveWaySwitch* fiveWaySwitch, SequencerInput *seqInput);
    SequencerPage(DisplaySSD1351_128x128x16_SPI* display, EncoderInput* encoder, FiveWaySwitch* fiveWaySwitch, Page* pageLeft, SequencerInput *seqInput);

    virtual const char* getTitle();

    virtual Control* getControl(uint8_t x, uint8_t y);

    virtual uint8_t width();
    virtual uint8_t height();

protected:
    Control *controls[1][2];
};

#endif