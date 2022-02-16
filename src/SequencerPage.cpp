#include "SequencerPage.h"

SequencerPage::SequencerPage(DisplaySSD1327_128x128_I2C *display, SequencerInput *seqInput)
    : controls{
          {
              new SequenceControlBPM(4, 21, display),
              new PositionControl(84, 21, display, seqInput),
          },
      }
{
}

const char *SequencerPage::getTitle()
{
    return "Sequencer";
}

Control *SequencerPage::getControl(uint8_t x, uint8_t y)
{
    return controls[y][x];
}

uint8_t SequencerPage::width()
{
    return 2;
}

uint8_t SequencerPage::height()
{
    return 1;
}

PositionControl::PositionControl(int xPos, int yPos, DisplaySSD1327_128x128_I2C *display, SequencerInput *seqInput) : Control(xPos, yPos, display)
{
    this->seqInput = seqInput;
    this->w = 40;
    this->h = 18;
}

void PositionControl::draw()
{
    int step_pos = this->seqInput->getStepPosition();
    char s[5];
    snprintf(s, 5, "%d-%02d", step_pos + 1, step_pos + 8);
    printFixed(0, 0, "Pos");
    printFixed(0, 10, s);
}

void PositionControl::onEncoderChange(int increments)
{
    this->seqInput->moveBy(increments);
}