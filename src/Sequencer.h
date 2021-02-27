#ifndef _SEQUENCER_H_
#define _SEQUENCER_H_

#include <Arduino.h>

#define MAX_STEPS 8
#define MAX_CHANNELS 1

typedef void (*SequencerCallback)(uint8_t note);

class Sequencer
{
public:
    Sequencer();
    void setStep(uint8_t step, uint8_t pitch);

    void step(uint32_t * tick);
    void update();
    void registerCallback(SequencerCallback (*cb)(uint8_t));
// private:
    const uint8_t step_len = MAX_STEPS;
    uint8_t _sequence[MAX_STEPS];
    uint8_t _step;

    uint8_t _stack[MAX_CHANNELS];

    SequencerCallback (*cb)(uint8_t);
};

#endif