#include "gameObjects.h"
#include <SDL.h>
#include "../drawHelperFunctions.h"
#include "../init.h"

void SandGrain::setupGrainOfSand(int x, int y, int l) {
    this->x = x;
    this->y = y;
    this->l = l;
}
