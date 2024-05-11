//
// Created by antoni on 11/05/24.
//

#ifndef GAME_CURSOR_H
#define GAME_CURSOR_H


#include "texture.h"

class Cursor {
public:
    explicit Cursor(Texture* texture);
    void render();
private:
    Texture* texture;

    void blit(int x, int y, bool center);
};


#endif //GAME_CURSOR_H
