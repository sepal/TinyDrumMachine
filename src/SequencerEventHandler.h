#pragma once

#include <Arduino.h>
#include "Note.h"

class SequencerEventHandler {
public:
    virtual void handleOnEvent(Note* note) = 0;
    virtual void handleOffEvent(Note* note) = 0;
};