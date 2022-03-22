#ifndef _PAGE_H_
#define _PAGE_H_

#include <Arduino.h>
#include <lcdgfx.h>
#include "FiveWaySwitch.h"
#include "EncoderInput.h"
#include "EncoderHandler.h"
#include "Control.h"

class Page : public EncoderHandler, public FiveWaySwitchEventHandler
{
public:
    Page(DisplaySSD1351_128x128x16_SPI *display, EncoderInput *encoder, FiveWaySwitch *fiveWaySwitch);
    Page(DisplaySSD1351_128x128x16_SPI *display, EncoderInput *encoder, FiveWaySwitch *fiveWaySwitch, Page *pageLeft);

    virtual const char *getTitle() = 0;

    virtual void onEncoderChange(int offset) = 0;
    virtual void onNavigation(FiveWaySwitchButton button) = 0;

    virtual void buttonDown(FiveWaySwitchButton button);
    virtual void buttonUp(FiveWaySwitchButton button);

    virtual void onSelect() = 0;
    virtual void onBlur() = 0;

    void enablePageSelection();
    void setLeftPage(Page *page);
    void setRightPage(Page *page);
    void prevPage();
    void nextPage();

protected:
    Page *pageLeft = 0;
    Page *pageRight = 0;
    DisplaySSD1351_128x128x16_SPI *display;
    EncoderInput *encoder;
    FiveWaySwitch *fiveWaySwitch;
    bool pageSelection = false;
};

#endif