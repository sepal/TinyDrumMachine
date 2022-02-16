#include "ADSRControl.h"

ADSRController::ADSRController(int xPos, int yPos, DisplaySSD1327_128x128_I2C *display)
    : Control(xPos, yPos, display)
{
    this->w = 120;
    this->h = 8;
}

void ADSRController::setControlable(ADSRControlable *toControl)
{
    this->controlable = toControl;
}

AttackController::AttackController(int xPos, int yPos, DisplaySSD1327_128x128_I2C *display)
    : ADSRController(xPos, yPos, display)
{}

void AttackController::draw()
{

    char s[7];
    snprintf(s, 7, "%03d ms", (int)this->controlable->getAttack());
    printFixed(0, 0, "Atk:");
    printFixed(50, 0, s);
}

void AttackController::onEncoderChange(int increments)
{
    float attack = this->controlable->getAttack() + increments;
    if (attack > 1000.0f)
    {
        attack = 1000.0f;
    }
    else if (attack < 0.0f)
    {
        attack = 0.0f;
    }

    this->controlable->setAttack(attack);
    this->draw();
}

DecayController::DecayController(int xPos, int yPos, DisplaySSD1327_128x128_I2C *display)
    : ADSRController(xPos, yPos, display)
{}

void DecayController::draw()
{

    char s[7];
    snprintf(s, 7, "%03d ms", (int)this->controlable->getDecay());
    printFixed(0, 0, "Dec:");
    printFixed(50, 0, s);
}

void DecayController::onEncoderChange(int increments)
{
    float attack = this->controlable->getDecay() + increments;
    if (attack > 1000.0f)
    {
        attack = 1000.0f;
    }
    else if (attack < 0.0f)
    {
        attack = 0.0f;
    }

    this->controlable->setDecay(attack);
    this->draw();
}

SustainController::SustainController(int xPos, int yPos, DisplaySSD1327_128x128_I2C *display)
    : ADSRController(xPos, yPos, display)
{}

void SustainController::draw()
{

    char s[7];
    snprintf(s, 7, "%03f", this->controlable->getSustain());
    printFixed(0, 0, "Sus:");
    printFixed(50, 0, s);
}

void SustainController::onEncoderChange(int increments)
{
    float attack = this->controlable->getSustain() + ((float)increments / 100.0f);
    if (attack > 1.0f)
    {
        attack = 1.0f;
    }
    else if (attack < 0.0f)
    {
        attack = 0.0f;
    }

    this->controlable->setSustain(attack);
    this->draw();
}

ReleaseController::ReleaseController(int xPos, int yPos, DisplaySSD1327_128x128_I2C *display)
    : ADSRController(xPos, yPos, display)
{}

void ReleaseController::draw()
{

    char s[7];
    snprintf(s, 7, "%03d ms", (int)this->controlable->getRelease());
    printFixed(0, 0, "Rel:");
    printFixed(50, 0, s);
}

void ReleaseController::onEncoderChange(int increments)
{
    float attack = this->controlable->getRelease() + increments;
    if (attack > 5000.0f)
    {
        attack = 5000.0f;
    }
    else if (attack < 0.0f)
    {
        attack = 0.0f;
    }

    this->controlable->setRelease(attack);
    this->draw();
}