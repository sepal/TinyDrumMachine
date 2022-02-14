#ifndef _AUDIO_ENGINE_H_
#define _AUDIO_ENGINE_H_

#include "Audio.h"

/**
 * An audio engine is an object that play notes and output sound
 * through an AudioStream object.
 */
class AudioEngine
{
public:
    /**
     * The audio output object; 
     */
    virtual AudioStream* getOutput() = 0;

    /**
     * Play a note.
     */
    virtual void noteOn(uint8_t note, uint8_t velocity) = 0;

    /**
     * Stop playing a note.
     */
    virtual void noteOff(uint8_t note) = 0;

};

#endif