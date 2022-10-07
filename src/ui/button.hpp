#ifndef BUTTON_HPP
#define BUTTON_HPP
#include "string"
#include "../../libs/raylib/src/raylib.h"
#include "../Game.hpp"

bool button(Game* context, std::string label, Vector2 position, Vector2 size);

#endif

