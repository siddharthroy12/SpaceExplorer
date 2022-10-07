#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"
#include "../Game.hpp"

class Player : public Entity {
public:
    void _update();
    void _draw();
    Player(SpaceScreen* context);
    ~Player();
public:
};

#endif
