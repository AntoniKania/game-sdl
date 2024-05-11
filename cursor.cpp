#include "cursor.h"

Cursor::Cursor(Texture *texture) {
    this->texture = texture;
}

void Cursor::render() {
    int x, y;
    SDL_GetMouseState(&x, &y);
    blit(x, y, true);
}

void Cursor::blit(int x, int y, bool center) {
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture->getSDLTexture(), NULL, NULL, &dest.w, &dest.h);

    if (center) {
        dest.x -= dest.w / 2;
        dest.y -= dest.h / 2;
    }

    texture->render(x, y);
}