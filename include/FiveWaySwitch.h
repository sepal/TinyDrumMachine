#pragma once

#include <Arduino.h>
#include "Config.h"

#define FIVEWAY_SWITCH_BUTTON_UP 1
#define FIVEWAY_SWITCH_BUTTON_DOWN 0

/**
 * Defines the 5 buttons for the five way switch.
 */
enum FiveWaySwitchButton
{
    JOYSTICK_DIR_RIGHT = PIN_5W_SWITCH_RIGHT,
    JOYSTICK_DIR_UP = PIN_5W_SWITCH_UP,
    JOYSTICK_DIR_LEFT = PIN_5W_SWITCH_LEFT,
    JOYSTICK_DIR_DOWN = PIN_5W_SWITCH_DOWN,
    JOYSTICK_DIR_CENTER = PIN_5W_SWITCH_CENTER,
};

/**
 * Event handler fro the five way switch.
 */
class FiveWaySwitchEventHandler
{
public:
    virtual void buttonDown(FiveWaySwitchButton button) = 0;
    virtual void buttonUp(FiveWaySwitchButton button) = 0;
};

/**
 * Class to read a 5 way switch.
 */
class FiveWaySwitch
{
public:
    FiveWaySwitch();

    /**
     * Initialize all te pins.
     */
    void begin();

    /**
     * Read the current state.
     */
    void update();

    /**
     * Register an event handler.
     */
    void registerEventHandler(FiveWaySwitchEventHandler *handler);

    /**
     * Unregister the current handler
     */
    void unregisterEventHandler();

protected:
    uint8_t last[5];
    const unsigned long debounceDelay = 65;
    unsigned long lastDebounceTime[5];

    FiveWaySwitchEventHandler *handler;
};