#ifndef _SEQUENCER_INPUT_
#define _SEQUENCER_INPUT_

#include <Arduino.h>
#include "Grid.h"
#include "Sequencer.h"

class SequencerInput : public GridEventHandler
{
public:
    SequencerInput(Sequencer *sequencer, Grid *grid);
    void handleGridEvent(GridEvent *event);

protected:
    uint8_t note_to_pixel_num(uint8_t note);

    uint8_t pixel_to_note(uint8_t x);

    Sequencer *sequencer;
    Grid *grid;
};

#endif