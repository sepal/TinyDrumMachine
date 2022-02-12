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

#include "FiveWaySwitch.h"
#include "Sequencer.h"
#include "Sampler.h"
#include "Grid.h"
#include "SequencerInput.h"
#include "Stealth57.h"
#include "Menu.h"
#include "Pages.h"

#define FLASH_CHIP_SELECT 6

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

Page* pages[1] = {
  new SequencerPage(&display, &seqInput),
};
Menu menu(&display, pages, 1);

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


  Serial.begin(9600);
  AudioMemory(10);

  // Start SerialFlash
  if (!SerialFlash.begin(FLASH_CHIP_SELECT))
  {
    while (1)
    {
      Serial.println(F("Cannot access SPI Flash chip"));
      delay(1000);
    }
  }

  audioShield.enable();
  audioShield.volume(0.5);

  uClock.init();
  uClock.setClock16PPQNOutput(ClockOut16PPQN);
  uClock.setTempo(90);

  uClock.start();
  display.begin();
  display.setFixedFont(stealth5710x8);

  grid.begin();
  grid.registerHandler(&seqInput);
  grid.show();

  sequencer.registerInstrument(&sampler);


  fiveWaySwitch.begin();
  menu.begin();
  Serial.println("ready");
  fiveWaySwitch.registerEventHandler(&menu);

  menu.updatePageScreen();

}


void loop()
{
  grid.read();
  sequencer.update();
  fiveWaySwitch.update();
  menu.update();
}
