#include "blood_effect.h"

BloodPuddleEffect::BloodPuddleEffect(Texture *texture, int x, int y) {
    this->texture = texture;
    int textureWidth = 0;
    int textureHeight = 0;
    SDL_QueryTexture(texture->getSDLTexture(), NULL, NULL, &textureWidth, &textureHeight);
    this->mPosX = x - textureWidth / BLOOD_EFFECT_ANIMATION_FRAMES / 2 + 16;
    this->mPosY = y - textureHeight / 2 + 16;
    this->clipToRender = 0;
    this->frame = 0;

    setStripes(textureWidth, textureHeight);
}

void BloodPuddleEffect::setStripes(int textureWidth, int textureHeight) {
    for (int i = 0; i < BLOOD_EFFECT_ANIMATION_FRAMES; i++) {
        gSpriteClips[ i ].x = i * (textureWidth / BLOOD_EFFECT_ANIMATION_FRAMES);
        gSpriteClips[ i ].y =   0;
        gSpriteClips[ i ].w =  textureWidth / BLOOD_EFFECT_ANIMATION_FRAMES;
        gSpriteClips[ i ].h = textureHeight;
    }
}

void BloodPuddleEffect::render(int camX, int camY) {
    frame++;
    if (frame <= 80) {
        return;
    }
    if (frame >= 320) {
        clipToRender = 3;
        SDL_Rect* currentClip = &gSpriteClips[ clipToRender ];
        texture->render(mPosX - camX, mPosY - camY, currentClip);
    } else {
        if (frame % 80 == 0) {
            ++clipToRender;
        }
        SDL_Rect* currentClip = &gSpriteClips[ clipToRender ];
        texture->render(mPosX - camX, mPosY - camY, currentClip);
    }
}

BloodSpreadEffect::BloodSpreadEffect(Texture *texture, int shooterPosX, int shooterPosY, int victimPosX,
                                     int victimPosY) {
    this->texture = texture;
    int textureWidth = 0;
    int textureHeight = 0;
    SDL_QueryTexture(texture->getSDLTexture(), NULL, NULL, &textureWidth, &textureHeight);
    this->center = SDL_Point{0, textureHeight / 2};
    this->mPosX = victimPosX + 16;
    this->mPosY = victimPosY - textureHeight / 2 + 16;
    this->angle = calculateAngle(shooterPosX, shooterPosY, victimPosX, victimPosY);
}

double BloodSpreadEffect::calculateAngle(int shooterPosX, int shooterPosY, int victimPosX, int victimPosY) {
    int dx = victimPosX - shooterPosX;
    int dy = victimPosY - shooterPosY;

    double angleRadians = atan2(dy, dx);
    double angleDegrees = angleRadians * (180.0 / M_PI);

    while (angleDegrees < 0) {
        angleDegrees += 360.0;
    }
    while (angleDegrees >= 360.0) {
        angleDegrees -= 360.0;
    }

    return angleDegrees;
}

void BloodSpreadEffect::render(int camX, int camY) {
    texture->render(mPosX - camX, mPosY - camY, nullptr, angle, &center);

}

void BloodEffectCollection::renderBloodEffects(int camX, int camY) {
    for (auto& bloodEffect : bloodEffects) {
        bloodEffect->render(camX, camY);
    }
}

BloodEffectCollection::BloodEffectCollection(Texture *bloodPuddleTexture, Texture *bloodSpreadTexture) {
    this->bloodPuddleTexture = bloodPuddleTexture;
    this->bloodSpreadTexture = bloodSpreadTexture;
}

void BloodEffectCollection::createBloodEffects(int shooterPosX, int shooterPosY, int victimPosX, int victimPosY) {
    std::unique_ptr<BloodEffect> puddleEffect = std::make_unique<BloodPuddleEffect>(bloodPuddleTexture, victimPosX, victimPosY);
    std::unique_ptr<BloodEffect> spreadEffect = std::make_unique<BloodSpreadEffect>(bloodSpreadTexture, shooterPosX, shooterPosY, victimPosX, victimPosY);
    bloodEffects.push_back(std::move(puddleEffect));
    bloodEffects.push_back(std::move(spreadEffect));
}
