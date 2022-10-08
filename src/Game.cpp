#include "Game.hpp"
#include "screen/MainScreen.hpp"
#include <memory>

Game::Game() {
    // Load Assets
    this->asset.font = LoadFontEx("assets/fonts/monogram.ttf", 40, nullptr, 0);
    this->asset.titleBackgorund = LoadTexture("assets/title_background.png");
    this->asset.playerShipTexture = LoadTexture("assets/space_ship.png");
    this->asset.planetEarth = LoadTexture("assets/earth.png");

    // Set starting screen
    this->currentScreen = std::unique_ptr<Screen>(new MainScreen(this));
}

void Game::loop() {
    if (this->ui.mouseOnClickable) {
        SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
    } else {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }
    this->ui.mouseOnClickable = false;

    // Run the current screen loop
    this->currentScreen->loop();

    // Handle the change of screen
    if (this->screenNeedsToChange) {
        this->currentScreen.reset();
        this->currentScreen = this->nextScreen;
        this->screenNeedsToChange = false;
    }
}

void Game::changeCurrentScreen(std::shared_ptr<Screen> newScreen) {
    this->screenNeedsToChange = true;
    this->nextScreen = newScreen;
}

Game::~Game() {
}

