//
// Created by makstsar on 23.11.2021.
//

#include "../../include/elements/Dodecahedron.h"
#include <vector>
#include <glad.h>


Dodecahedron::Dodecahedron() {
    float fi = (1 + sqrt(5))/2;

    this->vertices = {
            -1/fi, 0.f, fi,          //0
            1/fi, 0.f, fi,           //1
            -1.f, 1.f, 1.f,          //2
            1.f, 1.f, 1.f,           //3
            -1.f, -1.f, 1.f,         //4
            1.f, -1.f, 1.f,          //5
            0.f, fi, 1/fi,           //6
            0.f, -fi, 1/fi,          //7
            -fi, 1/fi, 0.f,          //8
            -fi, -1/fi, 0.f,         //9
            -1.f, -1.f, -1.f,        //10
            -1/fi, 0.f, -fi,         //11
            0.f, -fi, -1/fi,         //12
            -1.f, 1.f, -1.f,         //13
            1.f, -1.f, -1.f,         //14
            1/fi, 0.f, -fi,          //15
            1.f, 1.f, -1.f,          //16
            0.f, fi, -1/fi,          //17
            fi, -1/fi, 0.f,          //18
            fi, 1/fi, 0.f            //19
    };

    this->indices = {
            2, 6, 8,
            6, 8, 13,
            6, 13, 17,

            0, 1, 2,
            1, 2, 6,
            1, 6, 3,

            0, 1, 5,
            0, 5, 7,
            0, 7, 4,

            0, 2, 4,
            2, 4, 8,
            4, 8, 9,

            4, 7, 9,
            9, 10, 12,
            7, 9, 12,

            5, 7, 18,
            7, 12, 18,
            12, 14, 18,

            10, 12, 14,
            10, 11, 14,
            11, 14, 15,

            14, 15, 16,
            14, 16, 18,
            16, 18, 19,

            1, 3, 5,
            3, 5, 18,
            3, 18, 19,

            3, 6, 19,
            6, 16, 17,
            6, 16, 19,

            11, 13, 17,
            11, 15, 17,
            15, 16, 17,

            8, 9, 10,
            8, 10, 11,
            8, 11, 13
    };

    this->indices_lines = {
        0, 1,
        0, 4,
        0, 2,
        1, 3,
        1, 5,
        2, 6,
        2, 8,
        3, 6,
        3, 19,
        4, 7,
        4, 9,
        5, 7,
        5, 18,
        6, 17,
        7,  12,
        8, 9,
        8, 13,
        9, 10,
        10, 11,
        10, 12,
        11, 13,
        11, 15,
        12, 14,
        13, 17,
        14, 15,
        14, 18,
        15, 16,
        16, 17,
        16, 19,
        18, 19
    };

    this->world_position = glm::vec3(-2.0f,  0.f,  -5.f);

    this->configuration_vertex_attributes();
}

void Dodecahedron::draw(Shader *shaderProgram) {
    shaderProgram->use();
    Figure::draw_lines(shaderProgram);
}
