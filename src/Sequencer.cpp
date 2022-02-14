
#include "Sequencer.h"

Sequencer::Sequencer()
{
    this->_step = 0;
    this->engine = NULL;
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
            if (this->engine != NULL)
            {
                this->engine->noteOn(this->_stack[i]->pitch, this->_stack[i]->velocity);
            }
            
            this->_stack[i] = NULL;
        }
    }
}

void Sequencer::registerAudioEngine(AudioEngine* engine)
{
    this->engine = engine;
}

void Sequencer::unregisterAudioEngine()
{
    this->engine = NULL;
}