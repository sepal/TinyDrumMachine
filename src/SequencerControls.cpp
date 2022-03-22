#include "SequenceControls.h"

SequenceControlBPM::SequenceControlBPM(int xPos, int yPos, LCD_TYPE *display) : Control(xPos, yPos, display)
{
    this->w = 40;
    this->h = 18;
}

void SequenceControlBPM::draw()
{

    float tempo = uClock.getTempo();
    char s[4];
    snprintf(s, 4, "%f", tempo);
    printFixed(0, 0, "BPM");
    printFixed(0, 10, s);
}

void SequenceControlBPM::onEncoderChange(int increments)
{
    float tempo = uClock.getTempo() + increments;
    uClock.setTempo(tempo);
}