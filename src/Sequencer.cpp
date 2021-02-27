
#include "Sequencer.h"

Sequencer::Sequencer() {
    this->_sequence[0] = 48;
    this->_sequence[1] = 0;
    this->_sequence[2] = 50;
    this->_sequence[3] = 0;
    this->_sequence[4] = 48;
    this->_sequence[5] = 0;
    this->_sequence[6] = 0;
    this->_sequence[7] = 50;


    for (int i=0; i<MAX_CHANNELS; i++) {
        this->_stack[i] = 0;
    }

    this->_step = 0;
}

void Sequencer::setStep(uint8_t step, uint8_t pitch) {
    this->_sequence[step] = pitch;
}

void Sequencer::step(uint32_t * tick) {
    this->_step = *tick % this->step_len;

    if (this->_sequence[this->_step] != 0) {

        for (int i=0; i<MAX_CHANNELS; i++) {
            if (this->_stack[i] == 0) {
                this->_stack[i] = this->_sequence[this->_step];
            }
        }
    }
}

void Sequencer::update() {
    for (int i=0; i<MAX_CHANNELS; i++) {
        if (this->_stack[i] != 0) {
            this->cb(this->_stack[i]);
            this->_stack[i] = 0;
        }
    }
}

void Sequencer::registerCallback(SequencerCallback (*cb)(uint8_t)) {
    this->cb = cb;
}