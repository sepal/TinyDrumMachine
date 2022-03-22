#ifndef _TEXT_PAGE_H_
#define _TEXT_PAGE_H_

#include "Config.h"
#include "Page.h"

class TextPage : public Page
{
public:
    TextPage(LCD_TYPE *display, EncoderInput *encoder, FiveWaySwitch *fiveWaySwitch);
    TextPage(LCD_TYPE *display, EncoderInput *encoder, FiveWaySwitch *fiveWaySwitch, Page *pageLeft);
    void onEncoderChange(int offset);
    void onNavigation(FiveWaySwitchButton button);

    void onSelect();
    void onBlur();

protected:
    uint8_t x = 0;
    uint8_t y = 0;
    Control *currentControl;

    virtual Control *getControl(uint8_t x, uint8_t y) = 0;

    virtual uint8_t width() = 0;
    virtual uint8_t height() = 0;

    void selectControl();
};

#endif