#include "Bullet.hpp"
#include "../screen/SpaceScreen.hpp"

Bullet::Bullet(SpaceScreen* context, Vector2 position, Vector2 velocity, BulletType) : Entity(context) {
    this->position = position;
    this->velocity = velocity;
    this->friction = false;
    this->velocityLimit = 0;
}

void Bullet::_draw() {
    Rectangle source;
    source.x = 0;
    source.y = 0;
    source.height = 32;
    source.width = 32;

    DrawTexturePro(
        this->context->context->asset.bullets,
        source,
        {
            .x = this->position.x,
            .y = this->position.y,
            .width = source.width,
            .height = source.height,
        },
        {
                (float)source.width/2,
                (float)source.height/2
        },
        Vector2Angle({0, 0,}, this->velocity)*RAD2DEG + 90,
        WHITE
    );
}

void Bullet::_update() {
    this->deadTimer -= GetFrameTime();

    if (this->deadTimer < 0) {
        this->isDead = true;
    }
}

Bullet::~Bullet() {
}
