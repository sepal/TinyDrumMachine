#ifndef _ADSR_CAPABLE_H_
#define _ADSR_CAPABLE_H_

#include <Arduino.h>
#include "ADSRControlable.h"

class ADSRCapable
{
public:
    virtual ADSRControlable *getADSRControlable(uint8_t i) = 0;
    virtual const char* getADSRControlableName(uint8_t i) = 0;
    virtual uint8_t maxADSRControlables() = 0;
};


#endif