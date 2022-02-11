#ifndef _CONTROL_H_
#define _CONTROL_H_

class Control {
public:
    Control(int xPos, int yPos, DisplaySSD1327_128x128_I2C* display) {
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
           this->display->drawRect(xPos-1, yPos-2, xPos + w + 2, yPos + h + 2);
        }
        this->display->printFixed(xPos + x, yPos + y, text);
    }

    int xPos;
    int yPos;
    int w;
    int h;
    bool selected;

    DisplaySSD1327_128x128_I2C* display;
};

#endif