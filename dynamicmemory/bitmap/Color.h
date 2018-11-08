#pragma once
#include <ctdint>

class Color {
private:
  uint32_t rgba;
public:
	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
		rgba = (r<<24) + (g<<16) + (b<<8) + a;
	}
	//TODO:	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha) {}

	char getColor(){
	    char color = 'white';
	    if(rgba == 0xFF0000FF):{color = red;}
	    else if(rgba == 0x00FF00FF):{color = green;}
	    else if(rgba == 0x000000FF):{color = black;}
	    else if(rgba == 0x0000FFFF):{color = blue;}
	    else if(rgba == 0xFFFFFFFF):{color = white;}

	    return color;
    }
};
