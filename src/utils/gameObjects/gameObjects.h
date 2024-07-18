#pragma once
#include <vector>
#include <SDL.h>
#include "../colors.h"
#include "../defs.h"
/**
 * Set the x, y, and l variables, then call `update` to update the 
 * `SDL_Rect drawRect`.  `render` will draw the `SDL_Rect drawRect`.
 */
class SandGrain
{
private:
    SDL_Rect drawRect;

public:
    int x;
    int y;
    int l;
    Color* color;
    void setupGrainOfSand(int x, int y, int l);
    void render();
};


/**
 * The grid is one pixel width, and intended to provide easy lookups to
 * where sand already is on the screen for colision detection and
 * updating.
 */
class Grid
{
public:
    int height;
    int width;
    int lookup[SCREEN_WIDTH][SCREEN_HEIGHT];  // (x,y)
    std::vector<SandGrain*> grainsOfSand;
    Grid createGrid();
    bool isInGrid(int x, int y);
    bool isOpenLocation(int x, int y);
    void addSandGrain(int x, int y);
    void updateSandGrain(SandGrain *sandGrain, int new_x, int new_y);
    void updateGrainsOfSand();
    void printLookup();
};