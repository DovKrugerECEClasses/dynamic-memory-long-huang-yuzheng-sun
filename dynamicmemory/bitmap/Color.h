//
// Created by Yuzheng Sun on 11/8/2018.
//
#pragma once
#include <cstdint>
#include <string>
using namespace std;

class Color {
private:
    uint32_t rgba;
public:
    Color(uint8_t r, uint8_t g, uint8_t b){
        rgba = (r<<24) + (g<<16) + (b<<8) + 255;
    }

    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a){
        rgba = (r<<24) + (g<<16) + (b<<8) + a;
    }
    //TODO:	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha) {}

    string getColor(){
        string color = "WHITE";
        if(rgba == 0xFF0000FF){color = "RED";}
        else if(rgba == 0x00FF00FF){color = "GREEN";}
        else if(rgba == 0x000000FF){color = "BLACK";}
        else if(rgba == 0x0000FFFF){color = "BLUE";}
        else if(rgba == 0xFFFFFFFF){color = "WHITE";}

        return color;
    }
};