#ifndef SCREEN_HPP
#define SCREEN_HPP

#include "../../libs/raylib/src/raylib.h"
#include "iostream"

class Game;

class Screen {
public:
    Screen(Game *context);
    virtual void loop() = 0;
    virtual ~Screen();
    Game *context;
};

#endif
