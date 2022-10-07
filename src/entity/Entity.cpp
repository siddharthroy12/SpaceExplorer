#include "Entity.hpp"

Entity::Entity(SpaceScreen* context) {
    this->context = context;
}

void Entity::update() {
    this->_update();

    // Handle the velocity limit
    if (Vector2Length(this->velocity) > this->velocityLimit) {
        this->velocity = Vector2Scale(Vector2Normalize(this->velocity), this->velocityLimit);
    }

    // Velocity
    this->position = Vector2Add(this->position, this->velocity);
}

void Entity::draw() {
    this->_draw();
}
