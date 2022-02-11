#include "SequencerInput.h"

SequencerInput::SequencerInput(Sequencer *sequencer, Grid *grid)
{
    this->sequencer = sequencer;
    this->grid = grid;
}

void SequencerInput::updateGrid()
{
    for (int y = 0; y < GRID_X; y++)
    {
        uint8_t pitch = this->pixel_to_note(y);
        Serial.println(pitch);
        for (int x = 0; x < GRID_Y; x++)
        {
            if (this->sequencer->getStep(this->step_position + x, pitch) == NULL)
            {
                grid->setPixelColor(x, y, seesaw_NeoPixel::Color(0, 0, 0));
            }
            else
            {
                grid->setColor(x, y, map(pitch % 12, 0, 12, 0, 255));
            }
        }
    }
    grid->show();
}

void SequencerInput::handleGridEvent(GridEvent *event)
{
    uint8_t pitch = pixel_to_note(event->y);
    uint8_t step = event->x + this->step_position;

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
            grid->setColor(event->x, event->y, map(pitch % 12, 0, 12, 0, 255));
        }
    }

    // // Turn on/off the neopixels!
    grid->show();
}

void SequencerInput::moveBy(int offset)
{
    if (this->step_position + 8 + offset > PATTERN_LEN)
    {
        this->step_position = PATTERN_LEN - 8 - 1;
    } else if(this->step_position + offset < 0) {
        this->step_position = 0;
    } else {
        this->step_position += offset;
    }
    this->updateGrid();
}

int SequencerInput::getStepPosition() {
    return this->step_position;
}

uint8_t SequencerInput::note_to_pixel_num(uint8_t note)
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

uint8_t SequencerInput::pixel_to_note(uint8_t x)
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