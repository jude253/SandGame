#include <SDL.h>
#include "init.h"
#include "common.h"
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif



void doInput(void)
{
    SDL_GetMouseState(
        &app.mousePosition.x,
        &app.mousePosition.y
    );
    

    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                #ifdef __EMSCRIPTEN__
                emscripten_cancel_main_loop();  /* this should "kill" the app. */
                #else
                exit(0);
                #endif
                break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_Log("Mouse position: x=%i y=%i",
                    app.mousePosition.x, app.mousePosition.y
                );
                app.mouseDown = true;
                break;
            case SDL_MOUSEBUTTONUP:
                app.mouseDown = false;
                SDL_Log("Mouse position: x=%i y=%i",
                    app.mousePosition.x, app.mousePosition.y
                );
                SDL_Log("app.mouseDown: %i",
                    app.mouseDown
                );
                // app.grid.printLookup();
                break;
            case SDL_KEYDOWN:
                app.currentColor = &app.randomColorsList[randomIntInRange(0, (int)app.randomColorsList.size())];
                break;
            default:
                break;
        }
    }
}