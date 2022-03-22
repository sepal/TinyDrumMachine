#ifndef _FILE_LOADER_PAGE_H_
#define _FILE_LOADER_PAGE_H_

#include <SdFat.h>
#include <SerialFlash.h>
#include "Config.h"
#include "Page.h"



class FileLoaderPage : public Page
{
public:
    FileLoaderPage(LCD_TYPE *display, EncoderInput *encoder, FiveWaySwitch *fiveWaySwitch);
    FileLoaderPage(LCD_TYPE *display, EncoderInput *encoder, FiveWaySwitch *fiveWaySwitch, Page *pageLeft);

    virtual const char *getTitle();

    virtual void onEncoderChange(int offset);
    virtual void onNavigation(FiveWaySwitchButton button);

    virtual void buttonDown(FiveWaySwitchButton button);
    virtual void buttonUp(FiveWaySwitchButton button);

    virtual void onSelect();
    virtual void onBlur();
protected:
    void listFiles();

    uint32_t offset;
};

#endif
