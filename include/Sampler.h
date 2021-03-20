#ifndef _SAMPLER_H_
#define _SAMPLER_H_

#include <Arduino.h>
#include <Audio.h>
#include "Note.h"
#include "Instrument.h"

#define MAX_SAMPLES 4

/**
 * Basic sampler instrument.s
 */
class Sampler: public Instrument {
public:
    Sampler();

    void noteOn(Note* note);
    void noteOff(Note* note);
    AudioStream* getOutput();

    AudioPlaySerialflashRaw* voices[MAX_SAMPLES];
    AudioConnection* patchCords[MAX_SAMPLES];
    AudioMixer4* out;

    uint8_t sample_notes[255];
    const char* samples[4] = {
        "01.RAW", "02.RAW", "03.RAW", "04.RAW"
    };
};

#endif