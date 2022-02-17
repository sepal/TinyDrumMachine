#include <Arduino.h>
#include <Audio.h>
#include <uClock.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <lcdgfx.h>
#include "Adafruit_NeoTrellis.h"
#include <Encoder.h>

#include "FiveWaySwitch.h"
#include "EncoderInput.h"
#include "Sequencer.h"
#include "DrumkitSampleEngine.h"
#include "Grid.h"
#include "SequencerInput.h"
#include "Stealth57.h"
#include "SequencerPage.h"
#include "ADSRPage.h"

#define FLASH_CHIP_SELECT 6

DisplaySSD1327_128x128_I2C display(-1);
AudioControlSGTL5000 audioShield;
Grid grid;
FiveWaySwitch fiveWaySwitch;
EncoderInput encoder;

Sequencer sequencer;
DrumkitSampleEngine drumkitSampler;

AudioOutputI2S out;
AudioConnection patchCord5(*drumkitSampler.getOutput(), 0, out, 0);
AudioConnection patchCord6(*drumkitSampler.getOutput(), 0, out, 1);
SequencerInput seqInput(&sequencer, &grid);

SequencerPage sequencerPage(&display, &encoder, &fiveWaySwitch, &seqInput);
ADSRPage adsrPage(&display, &encoder, &fiveWaySwitch, &drumkitSampler, &sequencerPage);

uint8_t last_button;
bool playing = false;

void onClockStart()
{
    playing = true;
}

void onClockStop()
{
    playing = false;
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

    pinMode(16, INPUT_PULLUP);

    Serial.begin(9600);
    delay(2000);
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
    uClock.setOnClockStartOutput(onClockStart);  
    uClock.setOnClockStopOutput(onClockStop);
    uClock.setTempo(90);

    display.begin();
    display.setFixedFont(stealth5710x8);

    grid.begin();
    grid.registerHandler(&seqInput);
    grid.show();

    sequencer.registerAudioEngine(&drumkitSampler);

    fiveWaySwitch.begin();
    fiveWaySwitch.registerEventHandler(&sequencerPage);
    encoder.registerEventHandler(&sequencerPage);
    sequencerPage.onSelect();

    last_button = digitalRead(16);

    Serial.println("Ready!");
}

void loop()
{
    grid.read();
    sequencer.update();
    fiveWaySwitch.update();
    encoder.update();

    uint8_t play_button = digitalRead(16);
    if (last_button != play_button)
    {
        if (play_button == LOW)
        {
            if (playing == true) {
                uClock.stop();
            }
            else
            {
                uClock.start();
            }
        }
        last_button = play_button;
    }
}
