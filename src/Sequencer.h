#ifndef _SEQUENCER_H_
#define _SEQUENCER_H_

#include <Arduino.h>
#include "Note.h"
#include "SequencerEventHandler.h"

#define PATTERN_LEN 8
#define MAX_VOICES 4
#define MAX_EVENT_HANDLERS 10

typedef void (*SequencerCallback)(uint8_t note);

class Sequencer
{
public:
    Sequencer();
    void setStep(uint8_t step, uint8_t pitch, uint8_t velocity);
    void removeStep(uint8_t step, uint8_t pitch);
    Note* getStep(uint8_t step, uint8_t pitch);

    void step(uint32_t * tick);
    void update();
    int8_t registerCallback(SequencerEventHandler*);
    void unregisterCallback(uint8_t i);
// private:
    const uint8_t step_len = PATTERN_LEN;
    Note *_sequence[PATTERN_LEN][256];
    uint8_t _step;

    Note *_stack[MAX_VOICES];

    SequencerEventHandler* eventHandlers[MAX_EVENT_HANDLERS];
};

#endif