#ifndef _ADSR_PAGE_H_
#define _ADSR_PAGE_H_

#include <lcdgfx.h>
#include "Pages.h"
#include "AudioEngine.h"
#include "ADSRControl.h"

class ADSRPage: public Page
{
public:
    ADSRPage(DisplaySSD1327_128x128_I2C *display, AudioEngineADSR* adsrEngine)
    {
        Serial.begin(9600);
        ADSRControlable* controlable = adsrEngine->getADSRControlable(0);
        attack = new AttackController(4, 16, display);
        decay = new DecayController(4, 32, display);
        sustain = new SustainController(4, 48, display);
        release = new ReleaseController(4, 64, display);

        Serial.println(adsrEngine->getADSRControlable(0)->getSustain());

        controls[0][0] = attack;
        controls[1][0] = decay;
        controls[2][0] = sustain;
        controls[3][0] = release;
        
        attack->setControlable(controlable);
        decay->setControlable(controlable);
        sustain->setControlable(controlable);
        release->setControlable(controlable);
    }

    virtual const char* getTitle()
    {
        return "ADSR";
    }

    virtual Control* getControl(uint8_t x, uint8_t y)
    {
        return this->controls[y][x];
    }

    virtual uint8_t width()
    {
        return 1;
    }

    virtual uint8_t height()
    {
        return 4;
    }

protected:
    AttackController* attack;
    DecayController* decay;
    SustainController* sustain;
    ReleaseController* release;
    Control *controls[4][1];
};

#endif