#ifndef _CONTROL_H_
#define _CONTROL_H_

#include "Config.h"

class Control {
public:
    Control(int xPos, int yPos, LCD_TYPE* display) {
        this->xPos = xPos;
        this->yPos = yPos;
        this->display = display;
        this->selected = false;
    }

    virtual void draw() = 0;
    virtual void onEncoderChange(int increments) = 0;

    void select() {
        this->selected = true;
    }

    void blur() {
        this->selected = false;
    }

protected:
    void printFixed(int x, int y, const char* text)
    {
        this->display->setColor(0xFF);
        if (selected) {
           this->display->drawRect(xPos, yPos-2, xPos + w + 2, yPos + h + 2);
        }
        else {
        this->display->setColor(0x00);
           this->display->drawRect(xPos, yPos-2, xPos + w + 2, yPos + h + 2);
        this->display->setColor(0xFF);
        }
        this->display->printFixed(xPos + x, yPos + y, text);
    }

    int xPos;
    int yPos;
    int w;
    int h;
    bool selected;

    LCD_TYPE* display;
};

#endif