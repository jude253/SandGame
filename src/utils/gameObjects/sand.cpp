#include "gameObjects.h"
#include <SDL.h>
#include "../drawHelperFunctions.h"

void SandGrain::setupGrainOfSand(int x, int y, int l) {
    this->x = x;
    this->y = y;
    this->l = l;
}


void SandGrain::render() {
    setRenderDrawColor(this->color);
    SDL_Rect drawRect;
    drawRect.x = this->x;
    drawRect.y = this->y;
    drawRect.w = this->l;
    drawRect.h = this->l;
    renderFillRect(drawRect);
}
