#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int MAP_WIDTH = 30;
const int MAP_HEIGHT = 20;

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 640;

class Map {
public:
    Map();
    ~Map();

    void draw();
private:
    std::vector<int> tiles;
};

class LTexture {
public:
    LTexture();

    ~LTexture();

    bool loadFromFile(std::string path);

    void free();

    void render(int x, int y, SDL_Rect* clip = NULL);

    int getWidth();
    int getHeight();

private:
    SDL_Texture* mTexture;

    int textureWidth;
    int textureHeight;
};

class Dot {
public:
    static const int DOT_WIDTH = 100;
    static const int DOT_HEIGHT = 100;

    static const int DOT_VEL = 10;

    Dot();

    void handleEvent(SDL_Event& e);

    void move();

    void render(int camX, int camY);

    int getPosX();
    int getPosY();

private:
    int mPosX, mPosY;
    int mVelX, mVelY;
};

bool init();

bool loadMedia();

void close();

SDL_Window* gWindow = NULL;

SDL_Renderer* gRenderer = NULL;

LTexture gDotTexture;
LTexture gGrayTexture;
LTexture gRedTexture;

Map::Map() {
    tiles = {
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
            1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
            1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
            1,1,2,1,2,2,2,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,1,1,1,1,
            1,1,2,1,1,1,1,1,1,1,2,2,2,2,1,1,1,1,2,1,1,1,1,1,1,2,1,1,1,1,
            1,1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,2,1,1,1,1,
            1,1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,2,1,1,1,1,
            1,1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,2,1,1,1,1,
            1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,2,1,1,1,1,
            1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,2,1,1,1,1,
            1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,2,2,1,1,1,
            1,1,2,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,2,1,1,1,
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,
            1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,
            1,1,1,1,1,1,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
    };
}

void Map::draw() {
    for (int i = 0; i <= MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            tiles[MAP_WIDTH * i + j] == 1 ? gGrayTexture.render(32 * j, 32 * i) : gRedTexture.render(32 * j, 32 * i);
        }
    }
}

Map::~Map() {
    if (!tiles.empty()) {
        //todo: destroy all textures??
        tiles = {};
    }
};

LTexture::LTexture() {
    mTexture = NULL;
    textureWidth = 0;
    textureHeight = 0;
}

LTexture::~LTexture() {
    free();
}

bool LTexture::loadFromFile(std::string path) {
    free();
    
    SDL_Texture* newTexture = NULL;
    
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    }
    else
    {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF ));
        
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
        if (newTexture == NULL) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }
        else {
            textureWidth = loadedSurface->w;
            textureHeight = loadedSurface->h;
        }
        
        SDL_FreeSurface(loadedSurface);
    }
    
    mTexture = newTexture;
    return mTexture != NULL;
}

void LTexture::render(int x, int y, SDL_Rect* clip) {
    SDL_Rect renderQuad = {x, y, textureWidth, textureHeight };

    if (clip != NULL) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}

int LTexture::getWidth() {
    return textureWidth;
}

int LTexture::getHeight() {
    return textureHeight;
}

void LTexture::free() {
    if(mTexture != NULL) {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        textureWidth = 0;
        textureHeight = 0;
    }
}

Dot::Dot() {
    mPosX = 0;
    mPosY = 0;

    mVelX = 0;
    mVelY = 0;
}

void Dot::handleEvent( SDL_Event& e ) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch(e.key.keysym.sym) {
            case SDLK_UP: mVelY -= DOT_VEL; break;
            case SDLK_DOWN: mVelY += DOT_VEL; break;
            case SDLK_LEFT: mVelX -= DOT_VEL; break;
            case SDLK_RIGHT: mVelX += DOT_VEL; break;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch(e.key.keysym.sym)
        {
            case SDLK_UP: mVelY += DOT_VEL; break;
            case SDLK_DOWN: mVelY -= DOT_VEL; break;
            case SDLK_LEFT: mVelX += DOT_VEL; break;
            case SDLK_RIGHT: mVelX -= DOT_VEL; break;
        }
    }
}

void Dot::move() {
    mPosX += mVelX;

    if (( mPosX < 0) || (mPosX + DOT_WIDTH > SCREEN_WIDTH)) {
        mPosX -= mVelX;
    }

    mPosY += mVelY;

    if (( mPosY < 0 ) || (mPosY + DOT_HEIGHT > SCREEN_HEIGHT ))
    {
        mPosY -= mVelY;
    }
}

void Dot::render(int camX, int camY) {
    gDotTexture.render(mPosX - camX, mPosY - camY);
}

int Dot::getPosX() {
    return mPosX;
}

int Dot::getPosY() {
    return mPosY;
}

bool init() {
    bool success = true;

    if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else {
        if (!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            printf("Warning: Linear texture filtering not enabled!");
        }

        gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        } else {
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if (gRenderer == NULL) {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            } else {
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                int imgFlags = IMG_INIT_PNG;
                if (!( IMG_Init( imgFlags ) & imgFlags)) {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }
    }

    return success;
}

bool loadMedia() {
    bool success = true;

    if (!gDotTexture.loadFromFile( "assets/dot.png")) {
        printf("Failed to load dot texture!\n");
        success = false;
    }

    if (!gGrayTexture.loadFromFile("assets/gray.png")) {
        printf("Failed to load background texture!\n");
        success = false;
    }

    if (!gRedTexture.loadFromFile("assets/red.png")) {
        printf("Failed to load background texture!\n");
        success = false;
    }

    return success;
}

void close() {
    gDotTexture.free();
    gGrayTexture.free();
    gRedTexture.free();

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* args[]) {
    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        if (!loadMedia()) {
            printf("Failed to load media!\n");
        } else {
            bool quit = false;

            SDL_Event e;

            Dot dot;

            Map map;

            SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

            while (!quit) {
                while (SDL_PollEvent( &e) != 0) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }

                    dot.handleEvent(e);
                }

                dot.move();

//                camera.x = (dot.getPosX() + Dot::DOT_WIDTH / 2) - SCREEN_WIDTH / 2;
//                camera.y = (dot.getPosY() + Dot::DOT_HEIGHT / 2) - SCREEN_HEIGHT / 2;

//                if (camera.x < 0) {
//                    camera.x = 0;
//                }
//                if (camera.y < 0) {
//                    camera.y = 0;
//                }
//                if (camera.x > LEVEL_WIDTH - camera.w) {
//                    camera.x = LEVEL_WIDTH - camera.w;
//                }
//                if (camera.y > LEVEL_HEIGHT - camera.h) {
//                    camera.y = LEVEL_HEIGHT - camera.h;
//                }

                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);

                map.draw();

                dot.render(camera.x, camera.y);

                SDL_RenderPresent(gRenderer);
            }
        }
    }

    close();

    return 0;
}