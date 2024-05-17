#ifndef GAME_TEXTURE_H
#define GAME_TEXTURE_H

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_ttf.h>

class Texture {
public:
    Texture();

    ~Texture();

    bool loadFromFile(std::string path);

    void free();
    void render(int x, int y, SDL_Rect* clip = nullptr, double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE );

    void setRenderer(SDL_Renderer *sdlRenderer);
    SDL_Renderer* getRenderer();
    int getWidth();
    int getHeight();
    SDL_Texture* getSDLTexture();
    bool loadFromRenderedText( std::string textureText, SDL_Color textColor, TTF_Font* font);
    bool createSemiTransparentTexture(int width, int height, Uint8 alpha);
private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;

    int textureWidth;
    int textureHeight;
};

#endif //GAME_TEXTURE_H
