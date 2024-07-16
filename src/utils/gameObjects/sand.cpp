#include "gameObjects.h"
#include <SDL.h>
#include "../drawHelperFunctions.h"

void SandGrain::setupGrainOfSand(int x, int y, int l) {
    this->x = x;
    this->y = y;
    this->l = l;

    SDL_Rect drawRect;
    drawRect.x = x;
    drawRect.y = y;
    drawRect.w = l;
    drawRect.h = l;

    this->drawRect = drawRect;
}

void SandGrain::update() {
    this->drawRect.x=this->x;
    this->drawRect.y=this->y;
    this->drawRect.w=this->l;
    this->drawRect.h=this->l;
}


void SandGrain::render() {
    setRenderDrawColor(this->color);
    renderFillRect(this->drawRect);
}
