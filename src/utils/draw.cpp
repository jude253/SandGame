#include <SDL.h>
#include <SDL_ttf.h>
#include "init.h"
#include "drawHelperFunctions.h"
#include "defs.h"
#include "input.h"
#include <string>


void prepareScene(void)
{
    setRenderDrawColor(BACKGROUND_COLOR);
    SDL_RenderClear(app.renderer);
}


void renderText(int x, int y, std::string text) {
    SDL_Color white = {255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), white);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(app.renderer, surface);
    int textWidth = surface->w;
    int textHeight = surface->h;
    SDL_FreeSurface(surface);
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = textWidth;
    rect.h = textHeight;
    SDL_RenderCopy(app.renderer, texture, NULL, &rect);
}

void renderFPS(void) {
    std::string writeOnScreen = "FPS=";
    writeOnScreen.append(std::to_string((int)app.fps));
    renderText(0, 0, writeOnScreen);
}

void presentScene(void)
{   
    renderFPS();

    if (app.mouseDown) {
        app.grid.addSandGrain(app.mousePosition.x, app.mousePosition.y);
    }
    app.grid.updateGrainsOfSand();

    for (int i = 0; i < app.grid.grainsOfSand.size(); i++) {
        SandGrain *sandGrain = app.grid.grainsOfSand[i];
        sandGrain->render();
    }

    SDL_RenderPresent(app.renderer);
}