#ifndef _ENCODER_HANDLER_H_
#define _ENCODER_HANDLER_H_

#include <Arduino.h>

class EncoderHandler
{
public:
    virtual void onEncoderChange(int offset) = 0;
};

#endif