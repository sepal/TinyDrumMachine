#ifndef _SAMPLER_H_
#define _SAMPLER_H_

#include <Arduino.h>
#include <Audio.h>
#include "Note.h"
#include "SequencerEventHandler.h"

#define MAX_SAMPLES 4

class Sampler: public SequencerEventHandler  {
public:
    Sampler();

    void play(uint8_t pitch);
    void stop(uint8_t pitch);
    AudioMixer4* getOutput();

    void handleOnEvent(Note* note);
    void handleOffEvent(Note* note);

    AudioPlaySerialflashRaw* voices[MAX_SAMPLES];
    AudioConnection* patchCords[MAX_SAMPLES];
    AudioMixer4* out;

    uint8_t sample_notes[255];
    const char* samples[4] = {
        "01.RAW", "02.RAW", "03.RAW", "04.RAW"
    };
};

#endif