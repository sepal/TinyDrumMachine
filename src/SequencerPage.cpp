#include "SequencerPage.h"

SequencerPage::SequencerPage(LCD_TYPE* display, EncoderInput* encoder, FiveWaySwitch* fiveWaySwitch, SequencerInput *seqInput)
    : TextPage(display, encoder, fiveWaySwitch),
     controls{
          {
              new SequenceControlBPM(4, 21, display),
              new PositionControl(84, 21, display, seqInput),
          },
      }
{
}

SequencerPage::SequencerPage(LCD_TYPE* display, EncoderInput* encoder, FiveWaySwitch* fiveWaySwitch, Page* pageLeft, SequencerInput *seqInput)
    : TextPage(display, encoder, fiveWaySwitch, pageLeft),
    controls{
          {
              new SequenceControlBPM(4, 21, display),
              new PositionControl(84, 21, display, seqInput),
          },
      }
{
}

const char *SequencerPage::getTitle()
{
    return "SEQ";
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

PositionControl::PositionControl(int xPos, int yPos, LCD_TYPE *display, SequencerInput *seqInput) : Control(xPos, yPos, display)
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