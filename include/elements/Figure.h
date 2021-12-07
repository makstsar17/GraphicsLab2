//
// Created by makstsar on 23.11.2021.
//

#ifndef GRAPHICSLAB2_FIGURE_H
#define GRAPHICSLAB2_FIGURE_H

#include <vector>
#include <glm/glm.hpp>
#include "../Shader.h"
#include "Elements.h"

class Figure: public Elements {
protected:
    unsigned int EBO_lines;

    glm::vec3 line_color = {0.f, 0.f, 0.f};
    glm::vec3 figure_color = {1.f, 0.5f, 0.f};

    std::vector<unsigned int> indices_lines;

    void configuration_vertex_attributes() override;

public:
    void draw_figure(Shader *shaderProgram);
    void draw_lines(Shader *shaderProgram);
    void draw_figure_with_lines(Shader *shaderProgram);

    virtual void draw(Shader *shaderProgram) = 0;

    std::string getType() override;

    void clear() override;
};


#endif //GRAPHICSLAB2_FIGURE_H
