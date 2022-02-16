#ifndef _ADSR_CONTROL_H_
#define _ADSR_CONTROL_H_

#include "lcdgfx.h"
#include "Control.h"
#include "ADSRControlable.h"
#include "AudioEngine.h"

class ADSRController : public Control
{
public:
    ADSRController(int xPos, int yPos, DisplaySSD1327_128x128_I2C *display);

    virtual void draw() = 0;
    virtual void onEncoderChange(int increments) = 0;

    void setControlable(ADSRControlable *toControl);

protected:
    ADSRControlable *controlable;
};

class AttackController : public ADSRController
{
public:
    AttackController(int xPos, int yPos, DisplaySSD1327_128x128_I2C *display);

    virtual void draw();
    virtual void onEncoderChange(int increments);
};

class DecayController : public ADSRController
{
public:
    DecayController(int xPos, int yPos, DisplaySSD1327_128x128_I2C *display);

    virtual void draw();
    virtual void onEncoderChange(int increments);
};

class SustainController : public ADSRController
{
public:
    SustainController(int xPos, int yPos, DisplaySSD1327_128x128_I2C *display);

    virtual void draw();
    virtual void onEncoderChange(int increments);
};

class ReleaseController : public ADSRController
{
public:
    ReleaseController(int xPos, int yPos, DisplaySSD1327_128x128_I2C *display);

    virtual void draw();
    virtual void onEncoderChange(int increments);
};

class ADSRControlSelector : public Control
{
public:
    ADSRControlSelector(int xPos, int yPos, DisplaySSD1327_128x128_I2C *display,
                        AttackController *attack, DecayController *decay, SustainController *sustain, ReleaseController *release,
                        AudioEngineADSR *engine);

    virtual void draw();
    virtual void onEncoderChange(int increments);

protected:
    ADSRController *adsr[4];
    AudioEngineADSR *engine;
    int i;
};

#endif