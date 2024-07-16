#pragma once

#include "colors.h"
#include "structs.h"

void setRenderDrawColor(Color color);
void renderFillRect(SDL_Rect rect);
void drawVertLine(int x, int y, int h);
/*
Draw vertically parallel trapezoid from x_lt to x_rt-- Left to Right.
*/
void drawVerticalTrapezoid(
    int x_lt, int y_lt, int x_rt, int y_rt,
    int x_lb, int y_lb, int x_rb, int y_rb
    );
