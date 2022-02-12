#ifndef _PAGES_H_
#define _PAGES_H_

#include "Arduino.h"
#include "Control.h"

class Page
{
public:
    virtual const char* getTitle() = 0;
    virtual Control* getControl(uint8_t x, uint8_t y) = 0;
    virtual uint8_t width() = 0;
    virtual uint8_t height() = 0;

protected:
};

#include "SequenceControls.h"

class SequencerPage : public Page
{
public:
    SequencerPage(DisplaySSD1327_128x128_I2C *display, SequencerInput *seqInput)
        : controls{
              {
                  new SequenceControlBPM(4, 21, display),
                  new PositionControl(84, 21, display, seqInput),
              },
          }
    {
    }

    virtual const char* getTitle()
    {
        return "Sequencer";
    }

    virtual Control* getControl(uint8_t x, uint8_t y)
    {
        return controls[y][x];
    }

    virtual uint8_t width() {
        return 2;
    };
    virtual uint8_t height() {
        return 1;
    }

protected:
    Control *controls[1][2];
};

#endif