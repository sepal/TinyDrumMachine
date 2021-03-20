#pragma once

#include <Arduino.h>
#include <Audio.h>
#include "Note.h"

/**
 * Abstract class for implementing instruments.
 * 
 * An instrument can receive midi note on and off events
 * and has an AudioStream over which sound is outputted.
 */
class Instrument {
public:
    /**
     * Called when a note is played.
     */
    virtual void noteOn(Note* note) = 0;

    /**
     * Currently unused
     */
    virtual void noteOff(Note* note) = 0;

    /**
     * Return the audio stream which produces the sound.
     */
    virtual AudioStream* getOutput() = 0;
};