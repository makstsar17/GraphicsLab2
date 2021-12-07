//
// Created by makstsar on 25.11.2021.
//

#include "../../include/elements/Graph.h"
#include <vector>
#include <glad.h>

Graph::Graph(const std::function<float(float, float)>& fn, float x_min, float x_max, float y_min, float y_max, float interval)
    : x_min(x_min), x_max(x_max), y_min(y_min), y_max(y_max), z_min(FLT_MAX), z_max(FLT_MIN), gridInterval(interval){

    setGrid(this->gridInterval, this->x_min, this->x_max, this->y_min, this->y_max);

    for(auto & grid_point : this->grid_points){
        for(auto & point: grid_point){
            this->vertices.push_back(point.x);
            this->vertices.push_back(point.y);

            auto z = fn(point.x, point.y);
            if(z < this->z_min)
                z_min = z;
            if(z > z_max)
                z_max = z;

            this->vertices.push_back(z);
        }
    }

    for(auto x = 0; x < this->grid_points.size(); x++){
        for(auto y = 0; y < this->grid_points[0].size() - 1; y++){
            this->indices.push_back(x * this->grid_points[0].size() + y);
            this->indices.push_back(x * this->grid_points[0].size() + y + 1);
        }
    }

    for(auto y = 0; y < this->grid_points[0].size(); y++){
        for(auto x = 0; x < this->grid_points.size() - 1; x++){
            this->indices.push_back(x * this->grid_points[0].size() + y);
            this->indices.push_back((x + 1) * this->grid_points[0].size() + y);
        }
    }

    this->world_position = glm::vec3(0.0f,  0.f,  0.f);

    this->configuration_vertex_attributes();
}

void Graph::draw(Shader *shaderProgram) {
    shaderProgram->use();
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    shaderProgram->setFloat("zMin", z_min);
//    shaderProgram->setFloat("zRange", (z_max-z_min));
    auto zRange = z_max-z_min;
    shaderProgram->setFloat("zRange", (zRange == 0) ? 1.0f : zRange);

    glDrawElements(GL_LINES, this->indices.size(),GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Graph::configuration_vertex_attributes() {
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);

    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
//    glBufferData(GL_ARRAY_BUFFER, this->vertices.size()*sizeof(float), &this->vertices[0], GL_DYNAMIC_DRAW); //STATIC_DRAW
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size()*sizeof(float), &this->vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size()*sizeof(unsigned int),
//                 &this->indices[0], GL_DYNAMIC_DRAW); //STATIC_DRAW
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size()*sizeof(unsigned int), &this->indices[0], GL_STATIC_DRAW);

//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)nullptr); // 3*size_of(float)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Graph::setGrid(float interval, float xMin, float xMax, float yMin, float yMax) {
    this->x_min = xMin;
    this->x_max = xMax;
    this->y_max = yMax;
    this->y_min = yMin;
    this->gridInterval = interval;

    this->grid_points.clear();

    for(auto x = x_min; x <= x_max; x += interval){
        std::vector<glm::vec2> v;
        for(auto y = y_min; y <= y_max; y+= interval)
            v.push_back(glm::vec2(x, y));

        this->grid_points.push_back(v);
    }
}

void Graph::clear() {
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
    glDeleteBuffers(1, &this->EBO);
}

std::string Graph::getType() {
    return "Graph";
}
