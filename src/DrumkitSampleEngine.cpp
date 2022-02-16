
#include "DrumkitSampleEngine.h"

DrumkitSampleBank::DrumkitSampleBank(const char *sampleName)
{
    this->sampleName = sampleName;
    this->samplePlayer = new AudioPlaySerialflashRaw();
    this->amp = new AudioAmplifier();
    this->env = new AudioEffectEnvelope();

    this->cords[0] = new AudioConnection(*this->samplePlayer, *this->amp);
    this->cords[1] = new AudioConnection(*this->amp, *this->env);

    this->env->delay(0.0);
    this->env->hold(0.0);

    this->amp->gain(1.0);
    this->setAttack(0.0);
    this->setDecay(0.0);
    this->setSustain(1.0);
    this->setRelease(10.0);
}

AudioStream *DrumkitSampleBank::getOutput()
{
    return this->env;
}

void DrumkitSampleBank::noteOn(uint8_t velocity)
{
    this->samplePlayer->play(sampleName);
    this->env->noteOn();
    this->amp->gain(VELOCITY_CURVES[velocityCurve][velocity]);
}

void DrumkitSampleBank::noteOff()
{
    this->env->noteOff();
}

void DrumkitSampleBank::setAttack(float milliseconds)
{
    this->env->attack(milliseconds);
    this->attack = milliseconds;
}

void DrumkitSampleBank::setDecay(float milliseconds)
{
    this->env->decay(milliseconds);
    this->decay = milliseconds;
}

void DrumkitSampleBank::setSustain(float level)
{
    this->env->sustain(level);
    this->sustain = level;
}

void DrumkitSampleBank::setRelease(float milliseconds)
{
    this->env->release(milliseconds);
    this->release = milliseconds;
}

float DrumkitSampleBank::getAttack()
{
    return attack;
}

float DrumkitSampleBank::getDecay()
{
    return decay;
}

float DrumkitSampleBank::getSustain()
{
    return sustain;
}

float DrumkitSampleBank::getRelease()
{
    return release;
}

DrumkitSampleEngine::DrumkitSampleEngine()
{
    for (int i = 0; i < DRUMKIT_MAX_BANKS; i++)
    {
        this->units[i] = new DrumkitSampleBank(banks[i]);
    }

    this->mixer[0] = new AudioMixer4();
    this->mixer[1] = new AudioMixer4();

    this->output = new AudioMixer4();

    this->cords[0] = new AudioConnection(*this->units[0]->getOutput(), 0, *this->mixer[0], 0);
    this->cords[1] = new AudioConnection(*this->units[1]->getOutput(), 0, *this->mixer[0], 1);
    this->cords[2] = new AudioConnection(*this->units[2]->getOutput(), 0, *this->mixer[0], 2);
    this->cords[3] = new AudioConnection(*this->units[3]->getOutput(), 0, *this->mixer[0], 3);

    this->cords[4] = new AudioConnection(*this->units[4]->getOutput(), 0, *this->mixer[1], 0);
    this->cords[5] = new AudioConnection(*this->units[5]->getOutput(), 0, *this->mixer[1], 1);
    this->cords[6] = new AudioConnection(*this->units[6]->getOutput(), 0, *this->mixer[1], 2);
    this->cords[7] = new AudioConnection(*this->units[7]->getOutput(), 0, *this->mixer[1], 3);

    this->cords[8] = new AudioConnection(*this->mixer[0], 0, *this->output, 0);
    this->cords[9] = new AudioConnection(*this->mixer[1], 0, *this->output, 1);

    this->sampleNotes[48] = 0;
    this->sampleNotes[50] = 1;
    this->sampleNotes[52] = 2;
    this->sampleNotes[53] = 3;
    this->sampleNotes[54] = 4;
    this->sampleNotes[55] = 5;
    this->sampleNotes[56] = 6;
    this->sampleNotes[57] = 7;
}

void DrumkitSampleEngine::noteOn(uint8_t note, uint8_t velocity)
{
    uint8_t bank_n = this->sampleNotes[note];
    this->units[bank_n]->noteOn(velocity);
}

void DrumkitSampleEngine::noteOff(uint8_t note)
{
    uint8_t bank_n = this->sampleNotes[note];
    this->units[bank_n]->noteOff();
}

AudioStream *DrumkitSampleEngine::getOutput()
{
    return this->output;
}

ADSRControlable* DrumkitSampleEngine::getADSRControlable(uint8_t i)
{
    return this->units[i];
}

const char* DrumkitSampleEngine::getADSRControlableName(uint8_t i)
{
    return this->adsrNames[i];
}

uint8_t DrumkitSampleEngine::maxADSRControlables()
{
    return 4;
}