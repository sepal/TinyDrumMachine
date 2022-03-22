#include "ADSRPage.h"

ADSRPage::ADSRPage(DisplaySSD1351_128x128x16_SPI* display, EncoderInput* encoder, FiveWaySwitch* fiveWaySwitch, ADSRCapable *adsrEngine)
    : TextPage(display, encoder, fiveWaySwitch)
{
    attack = new AttackController(4, 32, display);
    decay = new DecayController(4, 48, display);
    sustain = new SustainController(4, 64, display);
    release = new ReleaseController(4, 80, display);
    selector = new ADSRControlSelector(4, 16, display, attack, decay, sustain, release, adsrEngine);

    controls[0][0] = selector;
    controls[1][0] = attack;
    controls[2][0] = decay;
    controls[3][0] = sustain;
    controls[4][0] = release;
}

ADSRPage::ADSRPage(DisplaySSD1351_128x128x16_SPI *display, EncoderInput *encoder, FiveWaySwitch *fiveWaySwitch, ADSRCapable *adsrEngine, Page *pageLeft)
    : TextPage(display, encoder, fiveWaySwitch, pageLeft)
{
    attack = new AttackController(4, 32, display);
    decay = new DecayController(4, 48, display);
    sustain = new SustainController(4, 64, display);
    release = new ReleaseController(4, 80, display);
    selector = new ADSRControlSelector(4, 16, display, attack, decay, sustain, release, adsrEngine);

    controls[0][0] = selector;
    controls[1][0] = attack;
    controls[2][0] = decay;
    controls[3][0] = sustain;
    controls[4][0] = release;
}

const char *ADSRPage::getTitle()
{
    return "ADSR";
}

Control *ADSRPage::getControl(uint8_t x, uint8_t y)
{
    return this->controls[y][x];
}

uint8_t ADSRPage::width()
{
    return 1;
}

uint8_t ADSRPage::height()
{
    return 5;
}