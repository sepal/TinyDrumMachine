#ifndef _DRUMKIT_SAMPLE_ENGINE_H_
#define _DRUMKIT_SAMPLE_ENGINE_H_

#include <Audio.h>
#include "AudioConstants.h"
#include "AudioEngine.h"
#include "ADSRControl.h"

#define DRUMKIT_MAX_BANKS 8

class DrumkitSampleBank: public ADSRControlable
{
public:
    DrumkitSampleBank(const char* sampleName);

    AudioStream* getOutput();

    void noteOn(uint8_t velocity);
    void noteOff();

    int note();
    bool isPlaying();

    void setAttack(float milliseconds);
    void setDecay(float milliseconds);
    void setSustain(float level);
    void setRelease(float milliseconds);


    virtual float getAttack();
    virtual float getDecay();
    virtual float getSustain();
    virtual float getRelease();
protected:
    const char* sampleName;
    int velocityCurve = 1;

    AudioPlaySerialflashRaw* samplePlayer;
    AudioAmplifier* amp;
    AudioEffectEnvelope* env;
    AudioConnection* cords[2];

    float attack;
    float decay;
    float sustain;
    float release;
};

class DrumkitSampleEngine: public AudioEngineADSR
{
public:
    DrumkitSampleEngine();

    virtual AudioStream* getOutput();
    virtual void noteOn(uint8_t note, uint8_t velocity);
    virtual void noteOff(uint8_t note);
    virtual ADSRControlable* getADSRControlable(uint8_t i);
    virtual const char* getADSRControlableName(uint8_t i);
    virtual uint8_t maxADSRControlables();

protected:
    DrumkitSampleBank* units[DRUMKIT_MAX_BANKS];
    AudioMixer4* mixer[DRUMKIT_MAX_BANKS/4];
    AudioMixer4* output;
    AudioConnection* cords[10];


    uint8_t sampleNotes[255];
    const char* banks[DRUMKIT_MAX_BANKS] = {
        "01.RAW", "02.RAW", "03.RAW", "04.RAW", "05.RAW", "06.RAW", "07.RAW", "08.RAW"
    };

    const char* adsrNames[4] = {
        "Bank1", "Bank2", "Bank3", "Bank4"
    };
};

#endif