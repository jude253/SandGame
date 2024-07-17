#include "../defs.h"
#include "gameObjects.h"
#include "../init.h"
#include <iostream>

Grid Grid::createGrid() {
    Grid grid;
    grid.width = SCREEN_WIDTH;
    grid.height = SCREEN_HEIGHT;
    memset(grid.lookup, 0, sizeof(grid.lookup));
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
    sandGrain->color = getRandomColor();  // At the moment this drops up to 2FPS
    if (this->isOpenLocation(x,y)) {
        this->grainsOfSand.push_back(sandGrain);
        this->lookup[x][y] = 1;      
    }
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
    for (SandGrain *sandGrain: this->grainsOfSand) {
        int new_x = sandGrain->x;
        int new_y = sandGrain->y + 1;
        if (this->isOpenLocation(new_x, new_y)){
            this->lookup[sandGrain->x][sandGrain->y] = 0;
            this->lookup[new_x][new_y] = 1;
            sandGrain->x = new_x;
            sandGrain->y = new_y;
            sandGrain->update();
        }
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