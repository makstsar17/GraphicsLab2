//
// Created by makstsar on 25.11.2021.
//

#ifndef GRAPHICSLAB2_GRAPH_H
#define GRAPHICSLAB2_GRAPH_H

#include <vector>
#include <glm/glm.hpp>
#include <functional>
#include "../Shader.h"
#include "Elements.h"

class Graph: public Elements {
public:

    void configuration_vertex_attributes() override;

    void clear() override;

    Graph(const std::function<float(float, float)>& fn, float x_min, float x_max, float y_min, float y_max, float interval);

    void draw(Shader *shaderProgram) override;

    std::string getType() override;

private:
    float x_min;
    float x_max;
    float y_min;
    float y_max;
    float z_min;
    float z_max;
    float gridInterval;

    std::vector<std::vector<glm::vec2>> grid_points;

    void setGrid(float interval, float x_min, float x_max, float y_min, float y_max);
};


#endif //GRAPHICSLAB2_GRAPH_H
