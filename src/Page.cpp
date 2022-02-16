#include "Page.h"

Page::Page(DisplaySSD1327_128x128_I2C *display, EncoderInput *encoder, FiveWaySwitch *fiveWaySwitch)
{
    this->display = display;
    this->encoder = encoder;
    this->fiveWaySwitch = fiveWaySwitch;
}

Page::Page(DisplaySSD1327_128x128_I2C *display, EncoderInput *encoder, FiveWaySwitch *fiveWaySwitch, Page *pageLeft)
{
    this->display = display;
    this->encoder = encoder;
    this->fiveWaySwitch = fiveWaySwitch;
    this->pageLeft = pageLeft;
    this->pageLeft->setRightPage(this);
}

void Page::setLeftPage(Page *page)
{
    this->pageLeft = page;
}
void Page::setRightPage(Page *page)
{
    this->pageRight = page;
}
void Page::prevPage()
{
    if (!this->pageLeft)
    {
        return;
    }
    this->onBlur();
    this->pageLeft->onSelect();
    this->fiveWaySwitch->registerEventHandler(this->pageLeft);
    this->encoder->registerEventHandler(this->pageLeft);
}
void Page::nextPage()
{

    if (!this->pageRight)
    {
        return;
    }
    this->onBlur();
    this->pageRight->onSelect();
    this->fiveWaySwitch->registerEventHandler(this->pageRight);
    this->encoder->registerEventHandler(this->pageRight);
}