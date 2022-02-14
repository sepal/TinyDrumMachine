#ifndef _SEQUENCER_H_
#define _SEQUENCER_H_

#include <Arduino.h>
#include "Note.h"
#include "AudioEngine.h"

#define PATTERN_LEN 16
#define MAX_VOICES 8

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
    void registerAudioEngine(AudioEngine* engine);

    /**
     * Remove an instrument.
     */
    void unregisterAudioEngine();

protected:
    const uint8_t step_len = PATTERN_LEN;
    Note *_sequence[PATTERN_LEN][256];
    uint8_t _step;

    Note *_stack[MAX_VOICES];

    AudioEngine* engine;
};

#endif