#ifndef GAME_BLOOD_EFFECT_H
#define GAME_BLOOD_EFFECT_H


#include "texture.h"

class BloodEffect {
public:
    BloodEffect(Texture* texture, int x, int y);
    void render(int camX, int camY);
private:
    static const int BLOOD_EFFECT_ANIMATION_FRAMES = 4;
    SDL_Rect gSpriteClips[ BLOOD_EFFECT_ANIMATION_FRAMES ];
    Texture* texture;
    int mPosX, mPosY;
    int frame;
    int clipToRender;

    void setStripes(Texture *texture);
};

class BloodEffectCollection {
public:
    BloodEffectCollection(Texture* texture);
    void createBloodEffect(int mPosX, int mPosY);
    void renderBloodEffects(int camX, int camY);
    std::vector<BloodEffect> bloodEffects;
private:
    Texture* texture;
};


#endif //GAME_BLOOD_EFFECT_H
