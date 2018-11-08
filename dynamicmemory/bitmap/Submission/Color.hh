#pragma once
#include <iostream>

class Color {
private:
    uint32_t rgba;
public:
    Color(const uint8_t& r, const uint8_t& g, const uint8_t& b) {
        rgba = (r<<24) + (g<<16) + (b<<8) + 0xFF;
    }
    Color(const uint8_t& r, const uint8_t& g, const uint8_t& b, const uint8_t& a) {
        rgba = (r<<24) + (g<<16) + (b<<8) + a;
    }
    //TODO:	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha) {}

    uint32_t getRgba() const{
        return rgba;
    }
};



char getColor(const uint32_t rgba) {
    char color = ' ';
    if(rgba == 0xFF0000FF){color = 'R';}
    else if(rgba == 0x00FF00FF){color = 'G';}
    else if(rgba == 0x0000FFFF){color = 'B';}
    else if(rgba == 0x000000FF){color = 'b';}
    else if(rgba == 0xFFFFFFFF){color = 'W';}

    return color;
}
