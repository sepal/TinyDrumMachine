#ifndef _DRUMKIT_SAMPLE_ENGINE_H_
#define _DRUMKIT_SAMPLE_ENGINE_H_

#include <Audio.h>
#include "AudioConstants.h"
#include "AudioEngine.h"

#define DRUMKIT_MAX_BANKS 8

class DrumkitSampleBank
{
public:
    DrumkitSampleBank(const char* sampleName);

    AudioStream* getOutput();

    void noteOn(uint8_t velocity);
    void noteOff();

    int note();
    bool isPlaying();

    void attack(float milliseconds);
    void decay(float milliseconds);
    void sustain(float level);
    void release(float milliseconds);
protected:
    const char* sampleName;
    int velocityCurve = 1;

    AudioPlaySerialflashRaw* samplePlayer;
    AudioAmplifier* amp;
    AudioEffectEnvelope* env;
    AudioConnection* cords[2];
};

class DrumkitSampleEngine: public AudioEngine
{
public:
    DrumkitSampleEngine();

    virtual AudioStream* getOutput();
    virtual void noteOn(uint8_t note, uint8_t velocity);
    virtual void noteOff(uint8_t note);


    DrumkitSampleBank* getDrumkitSampleBank(uint8_t i);

protected:
    DrumkitSampleBank* units[DRUMKIT_MAX_BANKS];
    AudioMixer4* mixer[DRUMKIT_MAX_BANKS/4];
    AudioMixer4* output;
    AudioConnection* cords[10];


    uint8_t sampleNotes[255];
    const char* banks[DRUMKIT_MAX_BANKS] = {
        "01.RAW", "02.RAW", "03.RAW", "04.RAW", "05.RAW", "06.RAW", "07.RAW", "08.RAW"
    };

};

#endif;