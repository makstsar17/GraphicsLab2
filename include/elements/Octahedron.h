//
// Created by makstsar on 23.11.2021.
//

#ifndef GRAPHICSLAB2_OCTAHEDRON_H
#define GRAPHICSLAB2_OCTAHEDRON_H

#include "Figure.h"
#include "../Shader.h"

class Octahedron: public Figure{
public:
    Octahedron();

    void draw(Shader *shaderProgram) override;
};


#endif //GRAPHICSLAB2_OCTAHEDRON_H
