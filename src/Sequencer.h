#ifndef _SEQUENCER_H_
#define _SEQUENCER_H_

#include <Arduino.h>

#define PATTERN_LEN 8
#define MAX_VOICES 4

typedef void (*SequencerCallback)(uint8_t note);

struct Note {
    uint8_t pitch;
    uint8_t velocity = 0;
    
};

class Sequencer
{
public:
    Sequencer();
    void setStep(uint8_t step, uint8_t pitch, uint8_t velocity);
    void removeStep(uint8_t step, uint8_t pitch);
    Note* getStep(uint8_t step, uint8_t pitch);

    void step(uint32_t * tick);
    void update();
    void registerCallback(SequencerCallback (*cb)(uint8_t));
// private:
    const uint8_t step_len = PATTERN_LEN;
    Note *_sequence[PATTERN_LEN][256];
    uint8_t _step;

    Note *_stack[MAX_VOICES];

    SequencerCallback (*cb)(uint8_t);
};

#endif