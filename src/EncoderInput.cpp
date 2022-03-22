#include "EncoderInput.h"
#include "Config.h"

EncoderInput::EncoderInput()
{
    encoder = new Encoder(PIN_ENCODER_A, PIN_ENCODER_B);
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