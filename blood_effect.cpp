#include "blood_effect.h"

BloodEffect::BloodEffect(Texture *texture, int x, int y) {
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

void BloodEffect::setStripes(int textureWidth, int textureHeight) {
    for (int i = 0; i < BLOOD_EFFECT_ANIMATION_FRAMES; i++) {
        gSpriteClips[ i ].x = i * (textureWidth / BLOOD_EFFECT_ANIMATION_FRAMES);
        gSpriteClips[ i ].y =   0;
        gSpriteClips[ i ].w =  textureWidth / BLOOD_EFFECT_ANIMATION_FRAMES;
        gSpriteClips[ i ].h = textureHeight;
    }
}

void BloodEffect::render(int camX, int camY) {
    frame++;
    if (frame >= 400) {
        clipToRender = 3;
        SDL_Rect* currentClip = &gSpriteClips[ clipToRender ];
        texture->render(mPosX - camX, mPosY - camY, currentClip);
    } else {
        if (frame % 100 == 0) {
            ++clipToRender;
        }
        SDL_Rect* currentClip = &gSpriteClips[ clipToRender ];
        texture->render(mPosX - camX, mPosY - camY, currentClip);
    }
}

BloodEffectCollection::BloodEffectCollection(Texture *texture) {
    this->texture = texture;
}

void BloodEffectCollection::createBloodEffect(int mPosX, int mPosY) {
    BloodEffect effect = BloodEffect(texture, mPosX, mPosY);
    bloodEffects.push_back(effect);
}

void BloodEffectCollection::renderBloodEffects(int camX, int camY) {
    for (auto& bloodEffect : bloodEffects) {
        bloodEffect.render(camX, camY);
    }
}
