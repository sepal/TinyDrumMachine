#include "TextPage.h"

TextPage::TextPage(DisplaySSD1351_128x128x16_SPI *display, EncoderInput *encoder, FiveWaySwitch *fiveWaySwitch)
    : Page(display, encoder, fiveWaySwitch)
{
}
TextPage::TextPage(DisplaySSD1351_128x128x16_SPI *display, EncoderInput *encoder, FiveWaySwitch *fiveWaySwitch, Page *pageLeft)
    : Page(display, encoder, fiveWaySwitch, pageLeft)
{
}

void TextPage::onEncoderChange(int offset)
{
    getControl(x, y)->onEncoderChange(offset);
    getControl(x, y)->draw();
}

void TextPage::onNavigation(FiveWaySwitchButton button)
{
    switch (button)
    {
    case FiveWaySwitchButton::JOYSTICK_DIR_UP:
        if (y > 0)
        {
            y--;
        }
        else
        {
            this->enablePageSelection();
            return;
        }
        break;
    case FiveWaySwitchButton::JOYSTICK_DIR_RIGHT:
        if (x < this->width() - 1)
        {
            x++;
        }
        break;
    case FiveWaySwitchButton::JOYSTICK_DIR_DOWN:
        if (y < this->height() - 1)
        {
            y++;
        }
        break;
    case FiveWaySwitchButton::JOYSTICK_DIR_LEFT:
        if (x > 0)
        {
            x--;
        }
        break;

    default:
        break;
    }
    selectControl();
}

void TextPage::selectControl()
{
    if (currentControl)
    {
        currentControl->blur();
        currentControl->draw();
    }
    currentControl = this->getControl(x, y);
    currentControl->select();
    currentControl->draw();
}

void TextPage::onSelect()
{
    Page::onSelect();
    for (int y = 0; y < this->height(); y++)
    {
        for (int x = 0; x < this->width(); x++)
        {
            Control *c = this->getControl(x, y);
            c->blur();
            c->draw();
        }
    }
    if (!pageSelection)
    {
        selectControl();
    }
}

void TextPage::onBlur()
{
    this->currentControl->blur();
    this->currentControl->draw();
}