#include <Arduino.h>
#include <Audio.h>
#include <uClock.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <lcdgfx.h>
#include "Adafruit_NeoTrellis.h"
#define ENCODER_DO_NOT_USE_INTERRUPTS
#include <Encoder.h>

#include "Sequencer.h"
#include "Sampler.h"
#include "Grid.h"
#include "SequencerInput.h"
#include "FiveWaySwitch.h"

#include "Control.h"
#include "SequenceControls.h"
#include "RobotoMono.h"

#define FLASH_CHIP_SELECT  6

DisplaySSD1327_128x128_I2C display(-1);

Sequencer sequencer;
Sampler sampler;

AudioOutputI2S out;
AudioConnection patchCord5(*sampler.getOutput(), 0, out, 0);
AudioConnection patchCord6(*sampler.getOutput(), 0, out, 1);
AudioControlSGTL5000 audioShield;
Grid grid;
FiveWaySwitch fiveWaySwitch;
Encoder encoder(20, 21);
SequencerInput seqInput(&sequencer, &grid);

Control* currentControl = 0;

Control* controls[2] = {
  new SequenceControlBPM(4, 21, &display),
  new PositionControl(20, 60, &display, &seqInput),
};


long int encoder_old_pos = -99;


void selectNewControl(Control* newControl)
{
  if (currentControl)
    currentControl->blur();

  currentControl = newControl;
  currentControl->select();
}

void ClockOut16PPQN(uint32_t *tick)
{
  sequencer.step(tick);
}

void setup()
{
  // Audio shield has SCK on pin 14
  SPI.setSCK(14);
  // Audio shield has MOSI on pin 7
  SPI.setMOSI(7);

  fiveWaySwitch.begin();

  Serial.begin(9600);
  AudioMemory(10);

  // Start SerialFlash
  if (!SerialFlash.begin(FLASH_CHIP_SELECT)) {
    while (1) {
      Serial.println(F("Cannot access SPI Flash chip"));
      delay (1000);
    }
  }

  audioShield.enable();
  audioShield.volume(0.5);

  uClock.init();
  uClock.setClock16PPQNOutput(ClockOut16PPQN);
  uClock.setTempo(90);

  uClock.start();
  grid.begin();

  grid.registerHandler(&seqInput);
  grid.show();

  sequencer.registerInstrument(&sampler);

  display.begin();
  display.setFixedFont(RobotoMono13x17);
  display.clear();
  display.printFixed(53, 0, "SEQ");
  Serial.println("ready");

  selectNewControl(controls[1]);
  encoder_old_pos = encoder.read();

  for (int i=0; i<2; i++) {
    controls[i]->draw();
  }
}


void loop()
{
  long encoder_pos = encoder.read();

  if (encoder_old_pos != encoder_pos) {
    controls[1]->onEncoderChange(encoder_old_pos - encoder_pos);
    encoder_old_pos = encoder_pos;
    controls[1]->draw();
  }

  grid.read();
  sequencer.update();
  fiveWaySwitch.update();


}
