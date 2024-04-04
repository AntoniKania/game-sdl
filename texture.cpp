#include "texture.h"

Texture::Texture() {
    texture = NULL;
    textureWidth = 0;
    textureHeight = 0;
}

Texture::~Texture() {
    free();
}

void Texture::setRenderer(SDL_Renderer* sdlRenderer) {
    this->renderer = sdlRenderer;
}

bool Texture::loadFromFile(std::string path) {
    free();

    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF ));

        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface );
        if (newTexture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        else {
            textureWidth = loadedSurface->w;
            textureHeight = loadedSurface->h;
        }

        SDL_FreeSurface(loadedSurface);
    }

    texture = newTexture;
    return texture != NULL;
}

void Texture::render(int x, int y, SDL_Rect* clip) {
    SDL_Rect renderQuad = {x, y, textureWidth, textureHeight};

    if (clip != NULL) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopy(renderer, texture, clip, &renderQuad);
}

int Texture::getWidth() {
    return textureWidth;
}

int Texture::getHeight() {
    return textureHeight;
}

void Texture::free() {
    if(texture != NULL) {
        SDL_DestroyTexture( texture );
        texture = NULL;
        textureWidth = 0;
        textureHeight = 0;
    }
}