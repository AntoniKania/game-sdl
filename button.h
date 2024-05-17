#ifndef GAME_BUTTON_H
#define GAME_BUTTON_H


#include <SDL_rect.h>
#include "texture.h"

class Button {
public:
    Button(Texture *texture, int x, int y, int w, int h);
    ~Button();

    void render();
    bool isMouseAboveButton() const;
    void handleEvent(SDL_Event &e);
    bool isClicked();
    void reset();
private:
    SDL_Rect buttonRect;
    Texture* textTexture;
    int horizontalShift;
    int verticalShift;
    bool clicked;
};

#endif //GAME_BUTTON_H
