#ifndef _SEQUENCER_H_
#define _SEQUENCER_H_

#include <Arduino.h>
#include "Note.h"
#include "Instrument.h"

#define PATTERN_LEN 8
#define MAX_VOICES 4
#define SEQUENCER_MAX_INSTRUMENTS 10

/**
 * Defines a step sequencer which can play one instrument.
 */
class Sequencer
{
public:
    Sequencer();

    /**
     * Set the pitch and velocity for the given step.
     */
    void setStep(uint8_t step, uint8_t pitch, uint8_t velocity);
    
    /**
     * Remove a set pitch at the given step
     */ 
    void removeStep(uint8_t step, uint8_t pitch);
    
    /**
     * Get the set note at the given step for the given pitch
     */
    Note* getStep(uint8_t step, uint8_t pitch);

    /**
     * Move the sequencer for one step at 16PPQN.
     */
    void step(uint32_t * tick);

    /**
     * General update function.
     */
    void update();

    /**
     * Register an instrument to play.
     */
    void registerInstrument(Instrument* instrument);

    /**
     * Remove an instrument.
     */
    void unregisterInstrument();

protected:
    const uint8_t step_len = PATTERN_LEN;
    Note *_sequence[PATTERN_LEN][256];
    uint8_t _step;

    Note *_stack[MAX_VOICES];

    Instrument* instrument;
};

#endif