#include "Astroid.hpp"
#include "../screen/SpaceScreen.hpp"

Astroid::Astroid(SpaceScreen* context, Vector2 position, AstroidSize astroidSize) : Entity(context) {
    this->size = astroidSize;
    this->position = position;
}

void Astroid::_update() {
}

void Astroid::_draw() {
    Rectangle source;
    switch (this->size) {
        case AstroidSize::SMALL:
            source.x = 0;
            source.y = 0;
            source.width = 31;
            source.height = 31;
            break;
        case AstroidSize::MEDIUM:
            source.x = 31;
            source.y = 0;
            source.width = 48;
            source.height = 48;
            break;
        case AstroidSize::BIG:
            source.x = 0;
            source.y = 48;
            source.width = 48;
            source.height = 56;
            break;
    }
    DrawTexturePro(
        this->context->context->asset.astroids,
        source,
        {
            .x = this->position.x,
            .y = this->position.y,
            .width = source.width,
            .height = source.height,
        },
        {
                (float)source.width/2,
                (float)source.height/2
        },
        0,
        WHITE
    );
}

Astroid::~Astroid() {
}
