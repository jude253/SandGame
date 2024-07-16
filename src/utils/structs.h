#pragma once

#include <SDL.h>
#include "gameObjects/gameObjects.h"

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
    Uint64 secondsElapsed;  // Number of seconds since game start.
    Uint64 gameStart;  // Game start-- intended to be set by SDL_GetPerformanceCounter()
    Uint64 frameStart;  // Frame start-- intended to be set by SDL_GetPerformanceCounter()
    float renderFrameSeconds;  // Seconds to render current frame
    float fps;  // FPS calculated from previous frame start to current frame start
    SDL_Point mousePosition;
    bool mouseDown;
    Grid grid;
} App;

typedef struct {
    float x;
    float y;
} Point;
