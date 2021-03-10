
#include "Sequencer.h"

Sequencer::Sequencer()
{
    this->_step = 0;

    for (uint8_t i=0; i < MAX_EVENT_HANDLERS; i++)
    {
        this->eventHandlers[i] = NULL;
    }
}

void Sequencer::setStep(uint8_t step, uint8_t pitch, uint8_t velocity)
{
    this->_sequence[step][pitch] = new Note();
    this->_sequence[step][pitch]->pitch = pitch;
    this->_sequence[step][pitch]->velocity = velocity;
}

void Sequencer::removeStep(uint8_t step, uint8_t pitch)
{
    delete this->_sequence[step][pitch];
    this->_sequence[step][pitch] = NULL;
}

Note *Sequencer::getStep(uint8_t step, uint8_t pitch)
{
    return this->_sequence[step][pitch];
}

void Sequencer::step(uint32_t *tick)
{
    this->_step = *tick % this->step_len;

    for (uint8_t pitch = 48; pitch < 54; pitch++)
    {
        if (this->_sequence[this->_step][pitch] != NULL)
        {

            for (uint8_t i = 0; i < MAX_VOICES; i++)
            {
                if (this->_stack[i] == NULL)
                {
                    this->_stack[i] = this->_sequence[this->_step][pitch];
                    break;
                }
            }
        }
    }
}

void Sequencer::update()
{

    for (uint8_t i = 0; i < MAX_VOICES; i++)
    {
        if (this->_stack[i] != NULL)
        {
            for (uint8_t j=0; j < MAX_EVENT_HANDLERS; j++)
            {
                if (this->eventHandlers[j] != NULL)
                {
                    this->eventHandlers[j]->handleOnEvent(this->_stack[i]);
                }
            }
            this->_stack[i] = NULL;
        }
    }
}

int8_t Sequencer::registerCallback(SequencerEventHandler *handler)
{
    for (uint8_t i=0; i < MAX_EVENT_HANDLERS; i++)
    {
        if (this->eventHandlers[i] == NULL)
        {
            this->eventHandlers[i] = handler;
            return i;
        }
    }
    return -1;
}

void Sequencer::unregisterCallback(uint8_t i)
{
    if (i <= MAX_EVENT_HANDLERS)
    {
        this->eventHandlers[i] = NULL;
    }
}