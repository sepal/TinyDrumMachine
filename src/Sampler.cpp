
#include "Sampler.h"


Sampler::Sampler() {
    // Hardcoded note to sample mapping.
    this->sample_notes[48] = 0;
    this->sample_notes[50] = 1;
    this->sample_notes[52] = 2;
    this->sample_notes[53] = 3;
    
    // Audio setup.
    this->out = new AudioMixer4();

    for (int i=0; i < MAX_SAMPLES; i++) {
        this->voices[i] = new AudioPlaySerialflashRaw();
        this->patchCords[i] = new AudioConnection(*this->voices[i], 0, *this->out, i);
        this->out->gain(i, 0.4);
    }
}

void Sampler::handleOnEvent(Note* note)
{
    this->play(note->pitch);
}

void Sampler::handleOffEvent(Note* note)
{
    this->stop(note->pitch);
}

void Sampler::play(uint8_t pitch) {
    uint8_t i = this->sample_notes[pitch];
    this->voices[i]->play(this->samples[i]);
}

void Sampler::stop(uint8_t pitch) {
    uint8_t i = this->sample_notes[pitch];
    this->voices[i]->stop();
}

AudioMixer4* Sampler::getOutput() {
    return this->out;
}