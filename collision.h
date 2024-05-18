#ifndef GAME_COLLISION_H
#define GAME_COLLISION_H

#include <SDL.h>

class Collision
{
public:
    static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
};

#endif //GAME_COLLISION_H
