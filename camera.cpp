#include "camera.h"

Camera::Camera() {
    x = 0;
    y = 0;
    SCREEN_HEIGHT = 640;
    SCREEN_WIDTH = 960;
}

void Camera::setCamera(Player player) {
    int LEVEL_WIDTH = 3840;
    int LEVEL_HEIGHT = 2560;
    x = (player.getPosX() + Player::DOT_WIDTH / 2 ) - SCREEN_WIDTH / 2;
    y = (player.getPosY() + Player::DOT_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;

    if (x < 0) {
        x = 0;
    }
    if (y < 0) {
        y = 0;
    }
    if (x > LEVEL_WIDTH - SCREEN_WIDTH) {
        x = LEVEL_WIDTH - SCREEN_WIDTH;
    }
    if (y > LEVEL_HEIGHT - SCREEN_HEIGHT) {
        y = LEVEL_HEIGHT - SCREEN_HEIGHT;
    }
}

SDL_Rect Camera::getRect() {
    return SDL_Rect{x, y, SCREEN_WIDTH,SCREEN_WIDTH};
}