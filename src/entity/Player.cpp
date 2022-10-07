#include "Player.hpp"
#include "../screen/SpaceScreen.hpp"
#include "iostream"

Player::Player(SpaceScreen* context) : Entity(context) {
    this->position = {50, 50};
}

void Player::_update() {
    Vector2 mousePositionInWorld = GetScreenToWorld2D(GetMousePosition(), this->context->camera);
    Vector2 playerToMouse = Vector2Subtract(mousePositionInWorld, this->position);

    if (IsKeyDown(KEY_W)) {
        this->velocity = Vector2Add(this->velocity, Vector2Scale(Vector2Normalize(playerToMouse), GetFrameTime()));
    }
}

void Player::_draw() {
    Vector2 mousePositionInWorld = GetScreenToWorld2D(GetMousePosition(), this->context->camera);

    Vector2 playerToMouse = Vector2Subtract(this->position, mousePositionInWorld);

    float rotation = Vector2Angle({0, 0}, playerToMouse);

    DrawTexturePro(
        this->context->context->asset.playerShipTexture,
        {
            .x = 0,
            .y = 0,
            .width = (float)this->context->context->asset.playerShipTexture.width,
            .height = (float)this->context->context->asset.playerShipTexture.height
        },
        {
            .x = this->position.x,
            .y = this->position.y,
            .width = (float)this->context->context->asset.playerShipTexture.width,
            .height = (float)this->context->context->asset.playerShipTexture.height,
        },
        {
            (float)this->context->context->asset.playerShipTexture.width/2,
            (float)this->context->context->asset.playerShipTexture.height/2
        },
        (rotation*RAD2DEG) - 90.0f,
        WHITE
    );

}

Player::~Player() {
}
