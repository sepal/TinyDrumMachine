#include "FiveWaySwitch.h"

FiveWaySwitch::FiveWaySwitch()
{
    this->handler = NULL;
}

void FiveWaySwitch::begin()
{
    for (int i = 0; i < 5; i++)
    {
        pinMode(i, INPUT_PULLUP);
        this->last[i] = digitalRead(i);
    }
}

void FiveWaySwitch::update()
{
    if (this->handler == NULL) {
        return;
    }

    for (int i = 0; i < 5; i++)
    {
        uint8_t state = digitalRead(i);

        if ((millis() - this->lastDebounceTime[i]) > this->debounceDelay)
        {
            if (state != this->last[i])
            {
                this->last[i] = state;
                this->lastDebounceTime[i] = millis();

                if (state == FIVEWAY_SWITCH_BUTTON_UP)
                {
                    this->handler->buttonUp((FiveWaySwitchButton) i);
                }
                else
                {
                    this->handler->buttonDown((FiveWaySwitchButton) i);
                }
            }
        }
    }
}
