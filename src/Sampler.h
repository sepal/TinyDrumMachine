#ifndef _SAMPLER_H_
#define _SAMPLER_H_

#include <Arduino.h>
#include <Audio.h>
#include "AudioSampleBd.h"
#include "AudioSampleSd.h"
#include "AudioSampleCh.h"
#include "AudioSampleOh.h"


#define MAX_SAMPLES 4

class Sampler {
public:
    Sampler();

    void play(uint8_t pitch);
    AudioMixer4* getOutput();

    AudioPlayMemory* voices[MAX_SAMPLES];
    AudioConnection* patchCords[MAX_SAMPLES];
    AudioMixer4* out;

    uint8_t sample_notes[255];
    const unsigned int* const samples[MAX_SAMPLES] = {
        AudioSampleBd, AudioSampleSd, AudioSampleCh, AudioSampleOh
    };
};

#endif