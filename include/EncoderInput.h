#ifndef _ENCODER_INPUT_H_
#define _ENCODER_INPUT_H_

#include <Arduino.h>
#include "Encoder.h"
#include "EncoderHandler.h"

class EncoderInput
{
public:
    EncoderInput();
    void update();
    void registerEventHandler(EncoderHandler* handler);

protected:
    Encoder* encoder;
    EncoderHandler* handler;
    long encoderLastPos;
};

#endif