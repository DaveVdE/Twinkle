#ifndef PIXEL_INCLUDED
#define PIXEL_INCLUDED

#include <Arduino.h>

template <class value>
struct pixel {
    typedef value value_type;

    value red;
    value green;
    value blue;

    pixel() : red(0), green(0), blue(0) {}
    pixel(value red, value green, value blue) : red(red), green(green), blue(blue) {}
};

typedef pixel<uint8_t> pixel8;

#endif