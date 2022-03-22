#include "FileLoaderPage.h"

FileLoaderPage::FileLoaderPage(LCD_TYPE *display, EncoderInput *encoder, FiveWaySwitch *fiveWaySwitch)
    : Page(display, encoder, fiveWaySwitch)
{
}
FileLoaderPage::FileLoaderPage(LCD_TYPE *display, EncoderInput *encoder, FiveWaySwitch *fiveWaySwitch, Page *pageLeft)
    : Page(display, encoder, fiveWaySwitch, pageLeft)
{
}

const char *FileLoaderPage::getTitle()
{
    return "Load sample";
}

void FileLoaderPage::onEncoderChange(int offset) {

}

void FileLoaderPage::onNavigation(FiveWaySwitchButton button) {

}

void FileLoaderPage::buttonDown(FiveWaySwitchButton button) {

}

void FileLoaderPage::buttonUp(FiveWaySwitchButton button) {

}

void FileLoaderPage::onSelect() {

}

void FileLoaderPage::onBlur() {
    
}