#ifndef GAME_HPP
#define GAME_HPP
#include "./screen/Screen.hpp"
#include <memory>
#include "../libs/raylib/src/raylib.h"

struct Asset {
    Font font;
    Texture titleBackgorund;
    Texture playerShipTexture;
    Texture planetEarth;
};

struct UI {
    bool mouseOnClickable = false;
};

struct Settings {
};

class Game {
    public:
        Game();
        Asset asset;
        UI ui;
        void changeCurrentScreen(std::shared_ptr<Screen> newScreen);
        Settings settings;
        void loop();
        bool running = true;
        ~Game();
    private:
        std::shared_ptr<Screen> currentScreen;
        std::shared_ptr<Screen> nextScreen;
        bool screenNeedsToChange = false;
};

#endif

