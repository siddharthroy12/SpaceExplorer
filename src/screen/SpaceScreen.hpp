#ifndef SPACE_SCREEN_HPP
#define SPACE_SCREEN_HPP
#include "Screen.hpp"
#include "../entity/Player.hpp"
#include <unordered_map>
#include "string"

class SpaceScreen : public Screen {
public:
    SpaceScreen(Game* context);
    int seed = 343;
    void loop();
    ~SpaceScreen();
    Camera2D camera;
    Player *player;
private:
    RenderTexture background;
    std::unordered_map<std::string, RenderTexture> backgrounds;
};

#endif

