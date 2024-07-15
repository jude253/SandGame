#include <SDL.h>
#include "../structs.h"
#include "../drawHelperFunctions.h"
#include <vector>
#include <stdbool.h>
#include "../common.h"
#include "../init.h"
#include "../defs.h"

class ClickSquare {

public:
    Color color;  // RGBA color
    SDL_Rect drawRect;  // Actual Rect used to draw onscreen.  Update with other attributes.
    int l;  // Edge length
    Point position;  // (x,y) upper left corner float coordinates -- truncate before drawing.
    Point velocity;  // (x,y) float velocity components
    Point acceleration;  // (x,y) float velocity components
    Uint64 drawTime;  // Draw time-- intended to be set by SDL_GetPerformanceCounter()
};

ClickSquare createClickSquare(int x, int y, int l, Color color) {
    ClickSquare clickSquare;
    clickSquare.l = l;
    clickSquare.color = color;
    clickSquare.position.x=(float)x;
    clickSquare.position.y=(float)y;
    clickSquare.drawRect.h=clickSquare.l;
    clickSquare.drawRect.w=clickSquare.l;
    clickSquare.drawRect.x=clickSquare.position.x;
    clickSquare.drawRect.y=clickSquare.position.y;
    return clickSquare;
}

std::vector<ClickSquare> CLICK_SQUARES_LIST;

void drawClickSquare(App app, ClickSquare clickSquare) {
    setRenderDrawColor(clickSquare.color);
    SDL_RenderFillRect(app.renderer, &clickSquare.drawRect);
}

ClickSquare createRandomClickSquare() {
    SDL_Point point = getRandomPoint();
    int length = GRID_HEIGHT;
    int rand_x = randIntInRange(GRID_WIDTH, SCREEN_WIDTH-GRID_WIDTH-length);
    int rand_y = randIntInRange(GRID_HEIGHT, SCREEN_HEIGHT-GRID_HEIGHT-length);
    ClickSquare cs = createClickSquare(rand_x, rand_y, GRID_HEIGHT, BLUE);
    return cs;
}


ClickSquare createClickSquareAtMousePosition() {
    int length = 5;
    int x = app.mousePosition.x;
    int y = app.mousePosition.y;
    ClickSquare cs = createClickSquare(x, y, length, BLUE);
    return cs;
}


bool deleteClickSquareIfClicked() {
    for (int i=0; i<CLICK_SQUARES_LIST.size(); i++) {
        ClickSquare cs = CLICK_SQUARES_LIST[i];
        if (SDL_PointInRect(&app.mousePosition, &cs.drawRect)) {
            SDL_Log("CLICKED RECTANGLE!");
            CLICK_SQUARES_LIST.erase(CLICK_SQUARES_LIST.begin() + i );
            app.squaresClickedCount = app.squaresClickedCount + 1;
            SDL_Log("squaresClickedCount: %i", (int)app.squaresClickedCount);
            CLICK_SQUARES_LIST.push_back(createRandomClickSquare());
            return 1;
        }
    }
    return 0;
}


bool addClickSquareToCLICK_SQUARES_LIST() {
    ClickSquare cs = createClickSquareAtMousePosition();
    CLICK_SQUARES_LIST.push_back(cs);
    return 0;
}

bool updateSquares() {
    for (int i=0; i<CLICK_SQUARES_LIST.size(); i++) {
        ClickSquare *cs = &CLICK_SQUARES_LIST[i];
        if (cs->position.y < SCREEN_HEIGHT - 2*GRID_HEIGHT) {
            cs->position.y += 1;
            cs->drawRect.y = cs->position.y;
        }
        
    }
    return 0;
}