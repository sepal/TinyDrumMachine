#ifndef _PAGES_H_
#define _PAGES_H_

#include "Arduino.h"
#include "Control.h"

class Page
{
public:
    virtual const char* getTitle() = 0;
    virtual Control* getControl(uint8_t x, uint8_t y) = 0;
    virtual uint8_t width() = 0;
    virtual uint8_t height() = 0;

protected:
};

#endif