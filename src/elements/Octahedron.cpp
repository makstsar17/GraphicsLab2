//
// Created by makstsar on 23.11.2021.
//

#include "../../include/elements/Octahedron.h"

Octahedron::Octahedron() {
    this->vertices = {
            0.f, 0.f, 1.5f,  //0
            0.f, 1.5f, 0.f,  //1
            1.5f, 0.f, 0.f,  //2
            -1.5f, 0.f, 0.f, //3
            0.f, -1.5f, 0.f, //4
            0.f, 0.f, -1.5f, //5
    };

    this->indices = {
            0, 1, 2,
            0, 1, 3,
            0, 3, 4,
            0, 2, 4,
            5, 1, 2,
            5, 1, 3,
            5, 3, 4,
            5, 2, 4
    };

    this->indices_lines = {
            0, 1,
            0, 2,
            0, 3,
            0, 4,
            5, 1,
            5, 2,
            5, 3,
            5, 4,
            1, 2,
            2, 4,
            3, 4,
            1, 3
    };

    this->world_position = glm::vec3(2.f,  0.f,  -5.f);

    this->configuration_vertex_attributes();
}

void Octahedron::draw(Shader *shaderProgram) {
    shaderProgram->use();
    Figure::draw_figure_with_lines(shaderProgram);
}

