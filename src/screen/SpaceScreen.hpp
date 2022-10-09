#ifndef SPACE_SCREEN_HPP
#define SPACE_SCREEN_HPP
#include "Screen.hpp"
#include "../entity/Player.hpp"
#include <unordered_map>
#include "string"

#define MINIMAP_SIZE 200
#define MINIMAP_EXPAND_SIZE 500

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
    bool miniMapExpand = false;
};

#endif

