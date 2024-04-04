#ifndef GAME_TEXTURE_H
#define GAME_TEXTURE_H

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Texture {
public:
    Texture();

    ~Texture();

    bool loadFromFile(std::string path);

    void free();

    void render(int x, int y, SDL_Rect* clip = nullptr);

    void setRenderer(SDL_Renderer *sdlRenderer);
    int getWidth();
    int getHeight();

private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;

    int textureWidth;
    int textureHeight;
};

#endif //GAME_TEXTURE_H
