#include "EncoderInput.h"

EncoderInput::EncoderInput()
{
    encoder = new Encoder(20, 21);
}

void EncoderInput::update()
{
    long encoder_pos = encoder->read();

    if (encoderLastPos != encoder_pos)
    {
        if (handler)
        {
            handler->onEncoderChange(encoderLastPos - encoder_pos);
        }
        encoderLastPos = encoder_pos;
    }
}

void EncoderInput::registerEventHandler(EncoderHandler* handler)
{
    this->handler = handler;
}