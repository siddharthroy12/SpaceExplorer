#ifndef BULLET_HPP
#define BULLET_HPP

#include "Entity.hpp"
#include "../Game.hpp"

enum class BulletType { NORMAL, FIREBALL };

class Bullet : public Entity {
public:
    void _update();
    void _draw();
    Bullet(SpaceScreen* context, Vector2 position, Vector2 velocity, BulletType);
    ~Bullet();
    BulletType bulletType;
    bool isDead = false;
    float deadTimer = 3000; // 3 seconds
};

#endif

