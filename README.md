# ArduinoLEDStripMetronome
> A simple sketch to drive a WS2812 LED strip as a button controller metronome

My wife and I wrote this sketch to control the LED strips on her Halloween costume.

It uses the FastLed module to control a strip of 35 WS2812 LEDs wired into an Arduino Leonardo clone.

### Parts

The following parts were used in this project:

* [WS2812 LED strip](https://amzn.to/346ZEgx)
* [Arduino "Pro Micro" Clone](https://amzn.to/2Joc0ZR)
* [3 conductor 24AWG wire](https://amzn.to/2PnyApg)
* [Momentary switch](https://amzn.to/2BHXAiZ)

### Wiring

1. The WS2812 LED GND and 5V should be hooked up to the GND and VCC pings on the Arduino
2. The WS2812 LED signal should be hooked up to pin 2
3. The momentary switch should be wired to GND and pin 3

### Usage

When the device is powered on, it will be set to 100 BPM, moving the active LED along the strip and fading out LEDs before and after the active LED.

You can change the tempo by pressing the momentary switch in time with the beat.
