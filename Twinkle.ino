#include <Arduino.h>
#include "pixel.h"
#include <Adafruit_NeoPixel.h>

class Gradient {
    private:
        pixel8 _values[256];
    
    public:
        Gradient() {
            for (uint16_t index = 0; index < 128; ++index) {
                _values[index] = pixel8(index, index, index);
            }

            for (uint16_t index = 128; index < 256; ++index) {
                _values[index] = pixel8(255 - index, 255 - index, 255 - index);
            }
        }

        pixel8 operator() (uint8_t index) const {
            return _values[index];
        }
};

class Twinkle {
    private: 
        bool _running;
        uint8_t _phase;
        const Gradient& _gradient;
    
    public:
        Twinkle(const Gradient& gradient) : _running(false), _phase(0), _gradient(gradient) {}

        pixel8 operator() () {
            pixel8 result;

            if (_running) {
                result = _gradient(_phase++);

                if (_phase == 255) {
                    _phase = 0;
                    _running = false;
                }
            } else {
                bool lucky = random(1024) == 0;

                if (lucky) {
                    _running = true;
                }
            }

            return result;
        }
};

Gradient gradient;
Twinkle twinkles[10] = {
    Twinkle(gradient),
    Twinkle(gradient),
    Twinkle(gradient),
    Twinkle(gradient),
    Twinkle(gradient),
    Twinkle(gradient),
    Twinkle(gradient),
    Twinkle(gradient),
    Twinkle(gradient),
    Twinkle(gradient)
};

#define PIN 8

Adafruit_NeoPixel strip = Adafruit_NeoPixel(10, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
    strip.begin();
    strip.show();
}

void loop() {

    for (uint8_t index = 0; index < 10; ++index) {
        auto pixel = twinkles[index]();

        strip.setPixelColor(index, pixel.red, pixel.green, pixel.blue);
    }

    strip.show();

    delay(10); // max 50fps.
}

