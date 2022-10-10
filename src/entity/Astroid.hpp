#ifndef ASTROID_HPP
#define ASTROID_HPP

#include "Entity.hpp"
#include "../Game.hpp"

enum class AstroidSize { BIG, MEDIUM, SMALL };

class Astroid : public Entity {
public:
    void _update();
    void _draw();
    Astroid(SpaceScreen* context, Vector2 position, AstroidSize);
    ~Astroid();
    int health;
    AstroidSize size;
};

#endif
