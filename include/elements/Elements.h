//
// Created by makstsar on 26.11.2021.
//

#ifndef GRAPHICSLAB2_ELEMENTS_H
#define GRAPHICSLAB2_ELEMENTS_H

#include <vector>
#include <glm/glm.hpp>
#include "../Shader.h"

class Elements {
protected:
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    glm::vec3 world_position;

    virtual void configuration_vertex_attributes() = 0;
public:
    virtual void draw(Shader *shaderProgram) = 0;

    glm::vec3 getWorldPosition() const;

    virtual void clear() = 0;

    virtual std::string getType() = 0;

    void setWorldPosition(glm::vec3 pos);
};


#endif //GRAPHICSLAB2_ELEMENTS_H
