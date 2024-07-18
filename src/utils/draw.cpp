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


SDL_Rect renderText(int x, int y, std::string text) {
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
    return rect;
}

void renderCurrentColor(void) {
    std::string writeOnScreen = "Current Color:";
    SDL_Rect textRect = renderText(0, 0, writeOnScreen);
    SDL_Rect colorRect;
    colorRect.x = textRect.x + textRect.w;
    colorRect.y = textRect.y;
    colorRect.w = textRect.h;
    colorRect.h = textRect.h;
    setRenderDrawColor(app.currentColor);
    SDL_RenderFillRect(app.renderer, &colorRect);
}

void renderFPS(void) {
    std::string writeOnScreen = "FPS=";
    writeOnScreen.append(std::to_string((int)app.fps));
    renderText(0, SCREEN_HEIGHT-25, writeOnScreen);
}

void presentScene(void)
{   

    if (app.mouseDown) {
        for (int i = -10; i <= 10; i++) {
            for (int j = -10; j <= 10; j++) {
                if (i % 2 == 0 && j % 2 == 0) {
                    app.grid.addSandGrain(app.mousePosition.x+i, app.mousePosition.y+j);
                }
            }
        }
    }
    app.grid.updateGrainsOfSand();

    for (int i = 0; i < app.grid.grainsOfSand.size(); i++) {
        SandGrain *sandGrain = app.grid.grainsOfSand[i];
        sandGrain->render();
    }

    renderCurrentColor();
    renderFPS();
    SDL_RenderPresent(app.renderer);
}