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

#include "Config.h"
#include "FiveWaySwitch.h"
#include "EncoderInput.h"
#include "Sequencer.h"
#include "DrumkitSampleEngine.h"
#include "Grid.h"
#include "SequencerInput.h"
#include "Stealth57.h"
#include "SequencerPage.h"
#include "ADSRPage.h"

// The parameters are  RST pin, BUS number, CS pin, DC pin, FREQ (0 means default), CLK pin, MOSI pin
LCD_TYPE display(PIN_LCD_RESET, {-1, PIN_LCD_CS, PIN_LCD_DC, 0, -1, -1});
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
    pinMode(PIN_BUTTON_MID, INPUT_PULLUP);

    Serial.begin(9600);
    delay(2000);
    AudioMemory(10);

    // Start SerialFlash
    if (!SerialFlash.begin(PIN_AUDIO_MEM))
    {
        while (1)
        {
            Serial.println(F("Cannot access SPI Flash chip"));
            delay(1000);
        }
    }

    if (!(SD.begin(PIN_AUDIO_SD)))
    {
        // stop here if no SD card, but print a message
        while (1)
        {
            Serial.println("Unable to access the SD card");
            delay(500);
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

    last_button = digitalRead(PIN_BUTTON_MID);

    Serial.println("Ready!");

    File root = SD.open("/");
    File entry = root.openNextFile();
    bool finished = false;
    while (!entry) {
        Serial.print(entry.name());
        if (entry.isDirectory()) {
            Serial.println("/");
        } else {
            Serial.println("");
        }
        entry.close();
        entry = root.openNextFile();
    }
}

void loop()
{
    // grid.read();
    // sequencer.update();
    // fiveWaySwitch.update();
    // encoder.update();

    // uint8_t play_button = digitalRead(PIN_BUTTON_MID);
    // if (last_button != play_button)
    // {
    //     if (play_button == LOW)
    //     {
    //         if (playing == true)
    //         {
    //             uClock.stop();
    //         }
    //         else
    //         {
    //             uClock.start();
    //         }
    //     }
    //     last_button = play_button;
    // }
}
