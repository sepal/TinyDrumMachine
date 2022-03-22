#include "Page.h"

Page::Page(LCD_TYPE *display, EncoderInput *encoder, FiveWaySwitch *fiveWaySwitch)
{
    this->display = display;
    this->encoder = encoder;
    this->fiveWaySwitch = fiveWaySwitch;
}

Page::Page(LCD_TYPE *display, EncoderInput *encoder, FiveWaySwitch *fiveWaySwitch, Page *pageLeft)
{
    this->display = display;
    this->encoder = encoder;
    this->fiveWaySwitch = fiveWaySwitch;
    this->pageLeft = pageLeft;
    this->pageLeft->setRightPage(this);
}

void Page::buttonDown(FiveWaySwitchButton button)
{
    if (!pageSelection)
    {
        onNavigation(button);
        return;
    }

    switch (button)
    {
    case FiveWaySwitchButton::JOYSTICK_DIR_RIGHT:
        this->nextPage();
        return;
    case FiveWaySwitchButton::JOYSTICK_DIR_DOWN:
        pageSelection = false;
        onSelect();
        return;
    case FiveWaySwitchButton::JOYSTICK_DIR_LEFT:
        this->prevPage();
        break;
    default:
        break;
    }
}

void Page::buttonUp(FiveWaySwitchButton button)
{
}

void Page::enablePageSelection()
{

    this->display->drawRect(0, 0, 128, 10);
    this->onBlur();
    pageSelection = true;
}

void Page::onSelect()
{
    display->clear();

    const char *title = this->getTitle();
    int x = 64 - sizeof(title) * 5;
    display->printFixed(x, 1, title);

    if (this->pageLeft != 0)
        display->printFixed(4, 1, "<");
    if (this->pageRight != 0)
        display->printFixed(114, 1, ">");

    if (pageSelection)
        this->display->drawRect(0, 1, 128, 10);
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
    this->pageLeft->pageSelection = true;
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
    this->pageRight->pageSelection = true;
    this->pageRight->onSelect();
    this->fiveWaySwitch->registerEventHandler(this->pageRight);
    this->encoder->registerEventHandler(this->pageRight);
}