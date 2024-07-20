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
     * Using memset leads to a sinkhole with optimizations. Just set the
     * points with loops.
     */
    for (int i = 0; i < SCREEN_WIDTH; i++) {
        for (int j = 0; j < SCREEN_HEIGHT; j++) {
            grid.lookup[i][j] = nullptr;
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
    return this->lookup[x][y] == nullptr;
}

void Grid::addSandGrain(int x, int y) {
    SandGrain *sandGrain = new SandGrain;
    sandGrain->setupGrainOfSand(x, y, 1);
    sandGrain->color = app.currentColor;
    if (this->isOpenLocation(x,y)) {
        this->grainsOfSand.push_back(sandGrain);
        this->lookup[x][y] = sandGrain;      
    }
}

void Grid::updateSandGrain(SandGrain *sandGrain, int new_x, int new_y) {
    this->lookup[sandGrain->x][sandGrain->y] = nullptr;
    this->lookup[new_x][new_y] = sandGrain;
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
void Grid::updateAndRenderGrainsOfSand() {
    // Set previous color to BACKGROUND_COLOR to ensure that it will be
    // set in Grid::renderSandGrain on first call.
    this->previousDrawColor = &BACKGROUND_COLOR;
    for (SandGrain *sandGrain: this->grainsOfSand) {
        int new_x = sandGrain->x;
        int new_y = sandGrain->y + 1;
        if (this->isOpenLocation(new_x, new_y)){
            this->updateSandGrain(sandGrain, new_x, new_y);
        }
        else if (isOpenLocation(new_x+1, new_y)) {
            int new_x_right = new_x+1;
            this->updateSandGrain(sandGrain, new_x_right, new_y);
        } else if (isOpenLocation(new_x-1, new_y)) {
            int new_x_left = new_x-1;
            this->updateSandGrain(sandGrain, new_x_left, new_y);
        }
        this->renderSandGrain(sandGrain);
    }
}

void Grid::updateGrainsOfSand() {
    // Set previous color to BACKGROUND_COLOR to ensure that it will be
    // set in Grid::renderSandGrain on first call.
    for (SandGrain *sandGrain: this->grainsOfSand) {
        int new_x = sandGrain->x;
        int new_y = sandGrain->y + 1;
        if (this->isOpenLocation(new_x, new_y)){
            this->updateSandGrain(sandGrain, new_x, new_y);
        }
        else if (isOpenLocation(new_x+1, new_y)) {
            int new_x_right = new_x+1;
            this->updateSandGrain(sandGrain, new_x_right, new_y);
        } else if (isOpenLocation(new_x-1, new_y)) {
            int new_x_left = new_x-1;
            this->updateSandGrain(sandGrain, new_x_left, new_y);
        }
    }
}

/**
 * This doesn't much improve the fps.  I think the main thing that could
 * help with this it could in theory be broken into grids, which could 
 * be faster, but I don't know if it is.  Not sure how to get a full 
 * 1280 x 720 screen full of sand without dropping frames.  It
 * doesn't seem like it should be tough, but it's giving me a headache.
 * 
 * 
 * This kind of works but it doesn't improve the FPS much as the screen
 * fills.  I think what would actually speed up the rendering is to
 * break the screen into chunks and see if the chunks need updating. If
 * not, save the chunk as a surface or texture, and only re-render 
 * chunks if they have a change.
 * 
 * I also think there might be a memory leak in this.  I wonder if it is
 * from creating a new surface pointer every frame or from the RGB
 * surfaces.
 */
void Grid::renderGrainsOfSand() {
    int w = SCREEN_WIDTH;
    int h = SCREEN_HEIGHT;
    SDL_Surface *surface = SDL_CreateRGBSurface(0,w,h,32,0,0,0,255);
    SandGrain* sandGrain;
    Uint32 drawColor;
   if (SDL_MUSTLOCK(surface)) SDL_LockSurface(surface);
    for (int x = 0; x < surface->w; x++) {
        for (int y = 0; y < surface->h; y++) {
            if (this->lookup[x][y] == nullptr) {
                drawColor = SDL_MapRGBA(surface->format, 
                BACKGROUND_COLOR.r, BACKGROUND_COLOR.g, BACKGROUND_COLOR.b, BACKGROUND_COLOR.a
                );
            } else {
                sandGrain = this->lookup[x][y];
                drawColor = SDL_MapRGBA(surface->format, 
                sandGrain->color->r, sandGrain->color->g, sandGrain->color->b, sandGrain->color->a
                );
            }
            *((Uint32*)surface->pixels + y * w + x) = drawColor;
        }
    }
    if (SDL_MUSTLOCK(surface)) SDL_UnlockSurface(surface);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(app.renderer, surface);
    SDL_FreeSurface(surface);
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = w;
    rect.h = h;
    SDL_RenderCopy(app.renderer, texture, NULL, &rect);
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