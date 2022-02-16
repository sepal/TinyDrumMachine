#ifndef _ADSR_PAGE_H_
#define _ADSR_PAGE_H_

#include <lcdgfx.h>
#include "TextPage.h"
#include "AudioEngine.h"
#include "ADSRControl.h"

class ADSRPage : public TextPage
{
public:
    ADSRPage(DisplaySSD1327_128x128_I2C* display, EncoderInput* encoder, FiveWaySwitch* fiveWaySwitch, ADSRCapable *adsrEngine);
    ADSRPage(DisplaySSD1327_128x128_I2C* display, EncoderInput* encoder, FiveWaySwitch* fiveWaySwitch, ADSRCapable *adsrEngine, Page* pageLeft);

    virtual const char *getTitle();
    virtual Control *getControl(uint8_t x, uint8_t y);
    virtual uint8_t width();
    virtual uint8_t height();

protected:
    AttackController *attack;
    DecayController *decay;
    SustainController *sustain;
    ReleaseController *release;
    ADSRControlSelector *selector;
    Control *controls[5][1];
};

#endif