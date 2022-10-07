#ifndef SPACE_SCREEN_HPP
#define SPACE_SCREEN_HPP
#include "Screen.hpp"
#include "../entity/Player.hpp"

class SpaceScreen : public Screen {
public:
    SpaceScreen(Game* context);
    void loop();
    ~SpaceScreen();
    Camera2D camera;
    Player *player;
};

#endif

