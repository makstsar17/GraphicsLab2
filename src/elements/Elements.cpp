//
// Created by makstsar on 26.11.2021.
//

#include "../../include/elements/Elements.h"

glm::vec3 Elements::getWorldPosition() const {
    return this->world_position;
}

void Elements::setWorldPosition(glm::vec3 pos) {
    this->world_position = pos;
}
