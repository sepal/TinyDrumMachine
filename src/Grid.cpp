#include "Grid.h"

Grid::Grid() : Adafruit_MultiTrellis((Adafruit_NeoTrellis *)trellis_array, GRID_X / 4, GRID_Y / 4)
{
    // for (uint8_t i = 0; i < 4; i++)
    // {
    //     this->activateKey(i, SEESAW_KEYPAD_EDGE_RISING);
    //     this->activateKey(i, SEESAW_KEYPAD_EDGE_FALLING);
    // }
}

bool Grid::begin()
{
    bool res = Adafruit_MultiTrellis::begin();

    for (uint8_t i = 0; i < this->GRID_NUM_PIXELS; i++)
    {
        this->activateKey(i, SEESAW_KEYPAD_EDGE_RISING);
        this->activateKey(i, SEESAW_KEYPAD_EDGE_FALLING);
    }
    return res;
}

void Grid::setColor(uint8_t x, uint8_t y, byte hue)
{
    uint32_t color = this->wheel(hue);
    this->setPixelColor(x, y, color);
}

void Grid::registerHandler(GridEventHandler *handler)
{
    this->handler = handler;
}

void Grid::unregisterHandler()
{
    this->handler = NULL;
}

void Grid::read()
{
    Adafruit_NeoTrellis *t;

    for (int n = 0; n < _rows; n++)
    {
        for (int m = 0; m < _cols; m++)
        {
            t = (_trelli + n * _cols) + m;

            uint8_t count = t->getKeypadCount();
            delayMicroseconds(500);
            if (count > 0)
            {
                count = count + 2;
                keyEventRaw e[count];
                t->readKeypad(e, count);
                for (int i = 0; i < count; i++)
                {
                    // call any callbacks associated with the key
                    e[i].bit.NUM = NEO_TRELLIS_SEESAW_KEY(e[i].bit.NUM);
                    if (e[i].bit.NUM < NEO_TRELLIS_NUM_KEYS &&
                        this->handler != NULL)
                    {
                        // update the event with the multitrellis number
                        GridEvent event;
                        event.edge = e[i].bit.EDGE;

                        int x = NEO_TRELLIS_X(e[i].bit.NUM);
                        int y = NEO_TRELLIS_Y(e[i].bit.NUM);

                        x = x + m * NEO_TRELLIS_NUM_COLS;
                        y = y + n * NEO_TRELLIS_NUM_ROWS;

                        event.num = y * NEO_TRELLIS_NUM_COLS * _cols + x;

                        event.x = x;
                        event.y = y;

                        this->handler->handleGridEvent(&event);
                    }
                }
            }
        }
    }
}

uint32_t Grid::wheel(byte WheelPos)
{
    if (WheelPos < 85)
    {
        return seesaw_NeoPixel::Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    }
    else if (WheelPos < 170)
    {
        WheelPos -= 85;
        return seesaw_NeoPixel::Color(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    else
    {
        WheelPos -= 170;
        return seesaw_NeoPixel::Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
    return 0;
}