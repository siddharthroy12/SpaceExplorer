#include "SpaceScreen.hpp"
#include "../helper.hpp"

SpaceScreen::SpaceScreen(Game* context) : Screen(context) {
    this->player = new Player(this);

    // Setup camera
    this->camera.target = {0, 0};
    this->camera.offset = {(float)getWindowWidth()/2, (float)getWindowHeight()/2};
    this->camera.zoom = 2;
    this->camera.rotation = 1;
}

void SpaceScreen::loop() {
    // Update
    this->camera.offset = {(float)getWindowWidth()/2, (float)getWindowHeight()/2};
    // Make camera follow player
    float cameraSpeed = GetFrameTime() * 6;
    this->camera.target.x = Lerp(this->camera.target.x, this->player->position.x, cameraSpeed);
    this->camera.target.y = Lerp(this->camera.target.y, this->player->position.y, cameraSpeed);

    player->update();

    // Draw
    BeginMode2D(this->camera);

    // ---- LAYER 3 ----

    // ---- LAYER 2 ----

    // ---- LAYER 1 ----

    // Draw Planet
    DrawTexture(this->context->asset.planetEarth, 0, 0, WHITE);

    // Draw player
    player->draw();



    EndMode2D();
}

SpaceScreen::~SpaceScreen() {
    delete this->player;
}

