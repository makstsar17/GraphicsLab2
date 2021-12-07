//
// Created by makstsar on 23.11.2021.
//

#include "../../include/elements/Figure.h"
#include <glad.h>

void Figure::draw_figure(Shader *shaderProgram) {
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    shaderProgram->setVec3("ourColor", this->figure_color.x, this->figure_color.y, this->figure_color.z);
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, nullptr);
}

void Figure::draw_lines(Shader *shaderProgram) {
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO_lines);
    shaderProgram->setVec3("ourColor", this->line_color.x, this->line_color.y, this->line_color.z);
    glDrawElements(GL_LINES, this->indices_lines.size(), GL_UNSIGNED_INT, 0);
}

void Figure::draw_figure_with_lines(Shader *shaderProgram) {
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    shaderProgram->setVec3("ourColor", this->figure_color.x, this->figure_color.y, this->figure_color.z);
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, nullptr);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO_lines);
    shaderProgram->setVec3("ourColor", this->line_color.x, this->line_color.y, this->line_color.z);
    glDrawElements(GL_LINES, this->indices_lines.size(), GL_UNSIGNED_INT, 0);
}

void Figure::clear() {
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
    glDeleteBuffers(1, &this->EBO);
    glDeleteBuffers(1, &this->EBO_lines);
}

void Figure::configuration_vertex_attributes() {

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO_lines);
    glGenBuffers(1, &this->EBO);

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size()*sizeof(float), &this->vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size()*sizeof(unsigned int),
                 &indices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO_lines);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices_lines.size()*sizeof(unsigned int),
                 &indices_lines[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

std::string Figure::getType() {
    return "Figure";
}

