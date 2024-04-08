#ifndef GAME_CAMERA_H
#define GAME_CAMERA_H

#include <SDL2/SDL.h>
#include "dot.h"

class Camera {
public:
    Camera();

    void setCamera(Dot dot);
    int x;
    int y;
    int SCREEN_WIDTH, SCREEN_HEIGHT;
    SDL_Rect getRect();
};


#endif //GAME_CAMERA_H
