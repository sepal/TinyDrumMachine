#ifndef _ADSR_PAGE_H_
#define _ADSR_PAGE_H_

#include <lcdgfx.h>
#include "Pages.h"
#include "AudioEngine.h"
#include "ADSRControl.h"

class ADSRPage : public Page
{
public:
    ADSRPage(DisplaySSD1327_128x128_I2C *display, AudioEngineADSR *adsrEngine)
    {
        ADSRControlable *controlable = adsrEngine->getADSRControlable(2);
        attack = new AttackController(4, 32, display);
        decay = new DecayController(4, 48, display);
        sustain = new SustainController(4, 64, display);
        release = new ReleaseController(4, 80, display);
        selector = new ADSRControlSelector(4, 16, display, attack, decay, sustain, release, adsrEngine);

        controls[0][0] = selector;
        controls[1][0] = attack;
        controls[2][0] = decay;
        controls[3][0] = sustain;
        controls[4][0] = release;
    }

    virtual const char *getTitle()
    {
        return "ADSR";
    }

    virtual Control *getControl(uint8_t x, uint8_t y)
    {
        return this->controls[y][x];
    }

    virtual uint8_t width()
    {
        return 1;
    }

    virtual uint8_t height()
    {
        return 5;
    }

protected:
    AttackController *attack;
    DecayController *decay;
    SustainController *sustain;
    ReleaseController *release;
    ADSRControlSelector *selector;
    Control *controls[5][1];
};

#endif