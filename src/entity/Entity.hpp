#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../../libs/raylib/src/raylib.h"
#include "../../libs/raylib/src/raymath.h"

class SpaceScreen;

class Entity {
public:
    Entity(SpaceScreen* context);
    void update();
    void draw();
    virtual void _update() = 0;
    virtual void _draw() = 0;
    virtual ~Entity() {};
    Vector2 position = {0, 0};
    Vector2 velocity = {0, 0};
    float angularVelocity = 0;
protected:
    SpaceScreen* context;
    float velocityLimit = 500;
};

#endif
