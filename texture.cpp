#include <SDL_ttf.h>
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

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF ));

        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface );
        if (newTexture == NULL) {
            printf("Unable to create bloodPuddleTexture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
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

SDL_Texture *Texture::getSDLTexture() {
    return this->texture;
}

void Texture::render(int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip) {
    SDL_Rect renderQuad = {x, y, textureWidth, textureHeight};

    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip );
}

bool Texture::loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font *font) {
    free();

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor );
    if (textSurface != NULL) {
        texture = SDL_CreateTextureFromSurface( renderer, textSurface );
        if (texture == NULL) {
            printf( "Unable to create textTexture from rendered text! SDL Error: %s\n", SDL_GetError() );
        } else {
            textureWidth = textSurface->w;
            textureHeight = textSurface->h;
        }

        SDL_FreeSurface( textSurface );
    }
    else {
        printf("Unable to load text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }

    return texture != NULL;
}

// LLM: write a method that will create a semitransparent background, that can be used to make the background darker...
bool Texture::createSemiTransparentTexture(int width, int height, Uint8 alpha) {
    if (texture) {
        SDL_DestroyTexture(texture);
    }

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
    if (!texture) {
        return false;
    }

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(renderer, texture);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, alpha);
    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer, nullptr);

    this->textureWidth = width;
    this->textureHeight = height;

    return true;
}

SDL_Renderer *Texture::getRenderer() {
    return renderer;
}
