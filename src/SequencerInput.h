#ifndef _SEQUENCER_INPUT_
#define _SEQUENCER_INPUT_

#include <Arduino.h>
#include "Grid.h"
#include "Sequencer.h"

class SequencerInput : public GridEventHandler
{
public:
    SequencerInput(Sequencer *sequencer, Grid *grid) {
        this->sequencer = sequencer;
        this->grid = grid;
    }


    void handleGridEvent(GridEvent *event)
    {
        uint8_t pitch = pixel_to_note(event->y);
        uint8_t step = event->x;

        // Check is the pad pressed?
        if (event->edge == SEESAW_KEYPAD_EDGE_RISING)
        {
            grid->setPixelColor(event->num, seesaw_NeoPixel::Color(200, 200, 200));
            if (this->sequencer->getStep(step, pitch) == NULL)
            {
                this->sequencer->setStep(step, pitch, 255);
            }
            else
            {
                sequencer->removeStep(step, pitch);
            }
        }
        else if (event->edge == SEESAW_KEYPAD_EDGE_FALLING)
        {
            if (this->sequencer->getStep(step, pitch) == NULL)
            {
                grid->setPixelColor(event->num, seesaw_NeoPixel::Color(0, 0, 0));
            }
            else
            {
                Serial.println(pitch % 12);
                grid->setColor(event->x, event->y, map(pitch % 12, 0, 12, 0, 255));
            }
        }

        // // Turn on/off the neopixels!
        grid->show();
    }

protected:
    uint8_t note_to_pixel_num(uint8_t note)
    {
        switch (note)
        {
        case 48:
            return 3;
        case 50:
            return 2;
        case 52:
            return 1;
        case 53:
            return 0;
        }
        return 0;
    }

    uint8_t pixel_to_note(uint8_t x)
    {
        switch (x)
        {
        case 3:
            return 48;
        case 2:
            return 50;
        case 1:
            return 52;
        case 0:
            return 53;
        }
        return 0;
    }

    Sequencer *sequencer;
    Grid *grid;
};

#endif