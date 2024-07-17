#include "colors.h"
#include "common.h"

Color RED                =   {.r = 255, .g = 0,   .b = 0,   .a = 255};
Color DARK_RED           =   {.r = 96,  .g = 0,   .b = 0,   .a = 255};
Color BLUE               =   {.r = 0,   .g = 0,   .b = 255, .a = 255};
Color GREEN              =   {.r = 0,   .g = 255, .b = 0,   .a = 255};
Color WHITE              =   {.r = 255, .g = 255, .b = 255, .a = 255};
Color BLACK              =   {.r = 0,   .g = 0,   .b = 0,   .a = 255};
Color BACKGROUND_COLOR   =   {.r = 96,  .g = 128, .b = 255, .a = 255};


Color getRandomColor() {
    int r,g,b;
    r = randomIntInRange(0, 255);
    g = randomIntInRange(0, 255);
    b = randomIntInRange(0, 255);

    Color randomColor = {
        .r = (Uint8)r, 
        .g = (Uint8)g,
        .b = (Uint8)b,
        .a = 255
    };
    return randomColor;
}