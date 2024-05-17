#include "button.h"

Button::Button(Texture *texture, int x, int y, int w, int h) {
    this->textTexture = texture;
    this->buttonRect = SDL_Rect{x, y, w, h};
    this->horizontalShift = (buttonRect.w - textTexture->getWidth()) / 2;
    this->verticalShift = (buttonRect.h - textTexture->getHeight()) / 2;
    this->clicked = false;
}

Button::~Button() {
    if (textTexture->getSDLTexture()) {
        SDL_DestroyTexture(textTexture->getSDLTexture());
    }
}

void Button::handleEvent(SDL_Event &e) {
    if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
        if (isMouseAboveButton()) {
            clicked = true;
        }

    }
}

bool Button::isMouseAboveButton() const {
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    return mouseX >= buttonRect.x && mouseX <= (buttonRect.x + buttonRect.w) &&
           mouseY >= buttonRect.y && mouseY <= (buttonRect.y + buttonRect.h);
}

void Button::reset() {
    clicked = false;
}

void Button::render() {
    SDL_RenderFillRect(textTexture->getRenderer(), &buttonRect);
    textTexture->render(buttonRect.x + horizontalShift, buttonRect.y + verticalShift);
}

bool Button::isClicked() {
    return clicked;
}
