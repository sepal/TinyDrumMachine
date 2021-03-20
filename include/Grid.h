#pragma once

#include <Arduino.h>
#include <Adafruit_NeoTrellis.h>

#define GRID_X 4
#define GRID_Y 8

#define GRID_GET_X(k) (k < 16 ? k % 4 : (k % 4) + 4)
#define GRID_GET_Y(k) (k < 16 ? k >> 2 : (k - 16) >> 2)
#define GRID_GET_N(x, y) ((x > 3 ? 1 : 0) * 12 + x + (y * 4))

struct GridEvent
{
    uint8_t edge : 2;  ///< the edge that was triggered
    uint16_t num : 14; ///< the event number
    uint8_t x;
    uint8_t y;
};

class GridEventHandler {
public:
    virtual void handleGridEvent(GridEvent *event) = 0;
};

class Grid: public Adafruit_MultiTrellis
{
public:
    Grid();

    bool begin();
    void setColor(uint8_t x, uint8_t y, byte wheelPos);
    void registerHandler(GridEventHandler *handler);
    void unregisterHandler();

    void read();

protected:
    static TrellisCallback handleKeyEvent(keyEvent evt);
    uint16_t trellisGetX(uint16_t num);
    uint16_t trellisGetY(uint16_t num);
    uint32_t wheel(byte WheelPos);

    const uint8_t GRID_NUM_PIXELS = GRID_X * GRID_Y;

    Adafruit_NeoTrellis trellis_array[GRID_X / 4][GRID_Y / 4] = {
        {Adafruit_NeoTrellis(0x2F), Adafruit_NeoTrellis(0x2E)}};

    GridEventHandler *handler;
};
