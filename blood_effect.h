#ifndef GAME_BLOOD_EFFECT_H
#define GAME_BLOOD_EFFECT_H


#include <memory>
#include "texture.h"

class BloodEffect
{
public:
    virtual ~BloodEffect() = default;
    virtual void render(int camX, int camY) = 0;
};

class BloodPuddleEffect : public BloodEffect {
public:
    BloodPuddleEffect(Texture* texture, int x, int y);
    virtual void render(int camX, int camY) override;
private:
    static const int BLOOD_EFFECT_ANIMATION_FRAMES = 4;
    SDL_Rect gSpriteClips[ BLOOD_EFFECT_ANIMATION_FRAMES ];
    Texture* texture;
    int mPosX, mPosY;
    int frame;
    int clipToRender;

    void setStripes(int textureWidth, int textureHeight);
};

class BloodSpreadEffect : public BloodEffect {
public:
    BloodSpreadEffect(Texture* texture, int shooterPosX, int shooterPosY, int victimPosX, int victimPosY);
    virtual void render(int camX, int camY);
private:
    Texture* texture;
    SDL_Point center;
    int mPosX, mPosY;
    double angle;

    double calculateAngle(int shooterPosX, int shooterPosY, int victimPosX, int victimPosY);
};

class BloodEffectCollection {
public:
    explicit BloodEffectCollection(Texture* bloodPuddleTexture, Texture* bloodSpreadTexture);
    void createBloodEffects(int shooterPosX, int shooterPosY, int victimPosX, int victimPosY);
    void renderBloodEffects(int camX, int camY);
    std::vector<std::unique_ptr<BloodEffect>> bloodEffects;
private:
    Texture* bloodPuddleTexture;
    Texture* bloodSpreadTexture;
};


#endif //GAME_BLOOD_EFFECT_H
