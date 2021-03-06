#ifndef _SEQUENCER_INPUT_
#define _SEQUENCER_INPUT_

#include <Arduino.h>
#include <lcdgfx.h>
#include "FiveWaySwitch.h"
#include "Grid.h"
#include "Sequencer.h"

class SequencerInput : public GridEventHandler, public FiveWaySwitchEventHandler
{
public:
    SequencerInput(Sequencer *sequencer, Grid *grid, DisplaySSD1306_128x64_I2C *display);
    void updateGrid();
    void handleGridEvent(GridEvent *event);
    void buttonDown(FiveWaySwitchButton button);
    void buttonUp(FiveWaySwitchButton button);



protected:
    uint8_t note_to_pixel_num(uint8_t note);
    uint8_t pixel_to_note(uint8_t x);

    Sequencer *sequencer;
    Grid *grid;
    DisplaySSD1306_128x64_I2C *display;

    uint8_t step_position = 0;
};

#endif