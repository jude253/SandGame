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


/**
 * The formula for the pointer arithmetic is confusing.
 */
void renderSurface(void) {
    int w = 200;
    int h = 100;
    SDL_Surface *surface = SDL_CreateRGBSurface(0,w,h,32,0,0,0,255);
    SDL_LockSurface(surface);
    for (int x = 0; x < surface->w; x++) {
        for (int y = 0; y < surface->h; y++) {
            if (x % 5 == 0 || y % 5 == 0)
                *((Uint32*)surface->pixels + y * w + x) = SDL_MapRGBA(surface->format, 255, 255, 255, 255);
            
        }
    }
    SDL_UnlockSurface(surface);
    
    SDL_Texture *texture = SDL_CreateTextureFromSurface(app.renderer, surface);
    SDL_Rect rect;
    rect.x = 200;
    rect.y = 200;
    rect.w = surface->w;
    rect.h = surface->h;
    SDL_RenderCopy(app.renderer, texture, NULL, &rect);
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
        for (int i = -5; i <= 5; i++) {
            for (int j = -5; j <= 5; j++) {
                if (i % 2 == 0 && j % 2 == 0) {
                    app.grid.addSandGrain(app.mousePosition.x+i, app.mousePosition.y+j);
                }
            }
        }
    }
    // app.grid.updateAndRenderGrainsOfSand();
    app.grid.updateGrainsOfSand();
    app.grid.renderGrainsOfSand();
    // renderSurface();


    renderCurrentColor();
    renderFPS();
    SDL_RenderPresent(app.renderer);
}