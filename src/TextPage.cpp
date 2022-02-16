#include "TextPage.h"

TextPage::TextPage(DisplaySSD1327_128x128_I2C *display, EncoderInput *encoder, FiveWaySwitch *fiveWaySwitch)
    : Page(display, encoder, fiveWaySwitch)
{
}
TextPage::TextPage(DisplaySSD1327_128x128_I2C *display, EncoderInput *encoder, FiveWaySwitch *fiveWaySwitch, Page *pageLeft)
    : Page(display, encoder, fiveWaySwitch, pageLeft)
{
}

void TextPage::onEncoderChange(int offset)
{
    getControl(x, y)->onEncoderChange(offset);
    getControl(x, y)->draw();
}

void TextPage::buttonDown(FiveWaySwitchButton button)
{
    switch (button)
    {
    case FiveWaySwitchButton::JOYSTICK_DIR_UP:
        if (y > 0)
        {
            y--;
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

void TextPage::buttonUp(FiveWaySwitchButton button) {}

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
    display->clear();
    display->printFixed(4, 0, this->getTitle());
    for (int y = 0; y < this->height(); y++)
    {
        for (int x = 0; x < this->width(); x++)
        {
            Control *c = this->getControl(x, y);
            c->draw();
        }
    }
    selectControl();
}

void TextPage::onBlur()
{
}