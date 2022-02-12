#ifndef _MENU_H_
#define _MENU_H_

#include "FiveWaySwitch.h"
#include "Pages.h"
#include "Control.h"
#include "Encoder.h"

class Menu : public FiveWaySwitchEventHandler
{
public:
    Menu(DisplaySSD1327_128x128_I2C* display, Page* pages[], uint8_t number_pages)
    : encoder(20, 21)
    {
        this->display = display;
        this->pages = pages;
        this->numPages = number_pages;
    }

    void begin()
    {
        encoderLastPos = encoder.read();
    }

    void updatePageScreen() {
        display->clear();
        display->printFixed(4, 0, pages[currentPage]->getTitle());
        for (int y=0; y<pages[currentPage]->height(); y++) {
            for (int x=0; x<pages[currentPage]->width(); x++) {
                Control* c = pages[currentPage]->getControl(x, y);
                c->draw();
            }
        }
        selectControl();
    }

    virtual void buttonDown(FiveWaySwitchButton button)
    {
        Serial.println((int)button);
        switch (button)
        {
        case FiveWaySwitchButton::JOYSTICK_DIR_UP:
            if (y > 0)
            {
                y--;
            }
            break;
        case FiveWaySwitchButton::JOYSTICK_DIR_RIGHT:
            if (x < pages[currentPage]->width()) {
                x++;
            }
            break;
        case FiveWaySwitchButton::JOYSTICK_DIR_DOWN:
            if (y < pages[currentPage]->height()) {
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

    virtual void buttonUp(FiveWaySwitchButton button) {}

    void update() {
        long encoder_pos = encoder.read();

        if (encoderLastPos != encoder_pos)
        {
            if (currentControl) {
                currentControl->onEncoderChange(encoderLastPos - encoder_pos);
                currentControl->draw();
            }
            encoderLastPos = encoder_pos;
        }
    }
protected:
    void selectControl()
    {
        if (currentControl) {
            currentControl->blur();
            currentControl->draw();
        }
        currentControl = pages[currentPage]->getControl(x, y);
        currentControl->select();
        currentControl->draw();
    }

    
    Page** pages;
    uint8_t numPages;
    uint8_t currentPage = 0;
    uint8_t x = 0;
    uint8_t y = 0;
    Control *currentControl;
    DisplaySSD1327_128x128_I2C* display;
    Encoder encoder;
    long encoderLastPos;
};

#endif