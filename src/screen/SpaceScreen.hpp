#ifndef SPACE_SCREEN_HPP
#define SPACE_SCREEN_HPP
#include "Screen.hpp"
#include "../entity/Player.hpp"
#include "../entity/Astroid.hpp"
#include "../entity/Bullet.hpp"
#include <unordered_map>
#include <string>
#include <vector>

#define MINIMAP_SIZE 200
#define MINIMAP_EXPAND_SIZE 500

struct Planet {
    bool invaded;
    Vector2 position;
};

struct StarSystem {
    std::vector<Planet> planets;
    std::vector<Astroid> astroids;
};

struct Playthrough {
    std::vector<StarSystem> starSystems;
    Playthrough(SpaceScreen* context, int seed);
    int currentStarSystem = 0;
    int seed;
};

class SpaceScreen : public Screen {
public:
    SpaceScreen(Game* context);
    Playthrough* playthrough;
    void loop();
    ~SpaceScreen();
    Camera2D camera;
    Player *player;
    std::vector<Bullet> bullets;
private:
    std::unordered_map<std::string, RenderTexture> backgrounds;
    bool miniMapExpand = false;
    bool paused = false;
};

#endif

