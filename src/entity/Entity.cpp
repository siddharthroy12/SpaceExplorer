#include "Entity.hpp"

Entity::Entity(SpaceScreen* context) {
    this->context = context;
}

void Entity::update() {
    this->_update();

    this->velocity.x = Lerp(this->velocity.x, 0, GetFrameTime());
    this->velocity.y = Lerp(this->velocity.y, 0, GetFrameTime());


    // Handle the velocity limit
    if (Vector2Length(this->velocity) > this->velocityLimit) {
        this->velocity = Vector2Scale(Vector2Normalize(this->velocity), this->velocityLimit);
    }

    // Velocity
    this->position = Vector2Add(this->position, Vector2Scale(this->velocity, GetFrameTime()));

}

void Entity::draw() {
    this->_draw();
}
