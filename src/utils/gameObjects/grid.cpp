#include "../defs.h"
#include "gameObjects.h"
#include "../init.h"
#include <iostream>
#include "../drawHelperFunctions.h"

Grid Grid::createGrid() {
    Grid grid;
    grid.width = SCREEN_WIDTH;
    grid.height = SCREEN_HEIGHT;

    /**
     * Somehow allocating more memory here for the color grid fixes the
     * sinkhole issue that occurs.  I don't understand why, but I think
     * something with the mouse movement is reusing the like a part of
     * the `grid.lookup` memory and causing an odd sinkhole effect with
     * optimizations.
     */
    memset(grid.lookup, 0, sizeof(grid.lookup));
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            grid.colorGrid[i][j] = nullptr;
        }
    }
    return grid;
}

bool Grid::isInGrid(int x, int y) {
    if (x < 0 || x >= SCREEN_WIDTH) {
        return false;
    }
    if (y < 0 || y >= SCREEN_HEIGHT) {
        return false;
    }
    return true;
}

bool Grid::isOpenLocation(int x, int y) {
    if (!this->isInGrid(x,y)) {
        return false;
    }
    return this->lookup[x][y] == 0;
}

void Grid::addSandGrain(int x, int y) {
    SandGrain *sandGrain = new SandGrain;
    sandGrain->setupGrainOfSand(x, y, 1);
    sandGrain->color = app.currentColor;
    if (this->isOpenLocation(x,y)) {
        this->grainsOfSand.push_back(sandGrain);
        this->lookup[x][y] = 1;      
    }
}

void Grid::updateSandGrain(SandGrain *sandGrain, int new_x, int new_y) {
    this->lookup[sandGrain->x][sandGrain->y] = 0;
    this->lookup[new_x][new_y] = 1;
    sandGrain->x = new_x;
    sandGrain->y = new_y;
}

void Grid::renderSandGrain(SandGrain* sandgrain) {
    if (sandgrain->color != this->previousDrawColor) {
        this->previousDrawColor = sandgrain->color;
        setRenderDrawColor(sandgrain->color);
    }
    SDL_RenderDrawPoint(app.renderer, sandgrain->x, sandgrain->y);
}

/**
 * For now, do not move sand down if it is at the bottom of the board or
 * if there is another grain of sand right below it.  This will have an
 * unintended consequence of not moving the top grain of sand down each
 * frame if 2 grains are drawn on top of each other, but for now this
 * is ok.  It would be better if I could have pointers to each grain of
 * sand, so I can update them in reverse order, I think? Not sure what
 * will be best.
 */
void Grid::updateGrainsOfSand() {
    // Set previous color to BACKGROUND_COLOR to ensure that it will be
    // set in Grid::renderSandGrain on first call.
    this->previousDrawColor = &BACKGROUND_COLOR;
    for (SandGrain *sandGrain: this->grainsOfSand) {
        int new_x = sandGrain->x;
        int new_y = sandGrain->y + 1;
        if (this->isOpenLocation(new_x, new_y)){
            this->updateSandGrain(sandGrain, new_x, new_y);
        } else if (isOpenLocation(new_x+1, new_y)) {
            int new_x_right = new_x+1;
            this->updateSandGrain(sandGrain, new_x_right, new_y);
        } else if (isOpenLocation(new_x-1, new_y)) {
            int new_x_left = new_x-1;
            this->updateSandGrain(sandGrain, new_x_left, new_y);
        }
        this->renderSandGrain(sandGrain);
    }
}


/**
 * For debugging purposes.
 */
void Grid::printLookup() {
    for (int i = 0; i < width; i++ ) {
        for (auto value: this->lookup[i]) {
            std::cout << value << ",";
        }
        std::cout << std::endl;
    }
}