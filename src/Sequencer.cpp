
#include "Sequencer.h"

Sequencer::Sequencer() {
    this->_step = 0;

    // for (uint8_t i = 0; i<MAX_VOICES; i++) {
    //     this->_stack[i] = NULL;
    // }

    // for (uint8_t step=0; step<this->step_len; step++) {
    //     for(uint8_t pitch=0; pitch<256; pitch++) {
    //         Serial.print(step);
    //         Serial.print("-");
    //         Serial.println(pitch);
    //         this->_sequence[step][pitch] = NULL;
    //     }
    // }
}

void Sequencer::setStep(uint8_t step, uint8_t pitch, uint8_t velocity) {
    this->_sequence[step][pitch] = new Note();
    this->_sequence[step][pitch]->pitch = pitch;
    this->_sequence[step][pitch]->velocity = velocity;
}

void Sequencer::removeStep(uint8_t step, uint8_t pitch) {
    delete this->_sequence[step][pitch];
    this->_sequence[step][pitch] = NULL;
}

Note* Sequencer::getStep(uint8_t step, uint8_t pitch) {
    return this->_sequence[step][pitch];
}

void Sequencer::step(uint32_t * tick) {
    this->_step = *tick % this->step_len;


    for (uint8_t pitch=48; pitch<54; pitch++) {
        if (this->_sequence[this->_step][pitch] != NULL) {

            for (uint8_t i=0; i<MAX_VOICES; i++) {
                if (this->_stack[i] == NULL) {
                    this->_stack[i] = this->_sequence[this->_step][pitch];
                    break;
                }
            }
        }
    }
}

void Sequencer::update() {
    // for (uint8_t i=0; i<MAX_VOICES; i++) {
    //     if (this->_stack[i] != 0) {
    //         this->cb(this->_stack[i]);
    //         this->_stack[i] = 0;
    //     }
    // }
}

void Sequencer::registerCallback(SequencerCallback (*cb)(uint8_t)) {
    this->cb = cb;
}