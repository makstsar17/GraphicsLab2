//
// Created by makstsar on 23.11.2021.
//

#ifndef GRAPHICSLAB2_DODECAHEDRON_H
#define GRAPHICSLAB2_DODECAHEDRON_H

#include "Figure.h"
#include "../Shader.h"

class Dodecahedron: public Figure{
public:
    Dodecahedron();

    void draw(Shader *shaderProgram) override;
};


#endif //GRAPHICSLAB2_DODECAHEDRON_H
