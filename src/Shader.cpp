//
// Created by makstsar on 18.11.2021.
//

#include <fstream>
#include <sstream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "../include/Shader.h"

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath) {
    std::string vertexCode, fragmentCode, geometryCode;
    std::fstream vShaderFile, fShaderFile, gShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try{
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream  vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

        if(!geometryPath.empty()){
            gShaderFile.open(geometryPath);
            std::stringstream gShaderStream;
            gShaderStream << gShaderFile.rdbuf();
            gShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::ifstream::failure& e){
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    auto vShaderCode = vertexCode.c_str();
    auto vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    checkErrors(vertex, "VERTEX");

    auto fShaderCode = fragmentCode.c_str();
    auto fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    checkErrors(fragment, "FRAGMENT");

    unsigned int geometry;
    if (!geometryPath.empty())
    {
        const char* gShaderCode = geometryCode.c_str();
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &gShaderCode, NULL);
        glCompileShader(geometry);
        checkErrors(geometry, "GEOMETRY");
    }

    this->ID = glCreateProgram();
    glAttachShader(this->ID, vertex);
    glAttachShader(this->ID, fragment);
    if (!geometryPath.empty()){
        glAttachShader(this->ID, geometry);
    }
    glLinkProgram(this->ID);

    GLint success;
    GLchar infoLog[1024];
    glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(this->ID, 1024, nullptr, infoLog);
        std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: PROGRAM\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if(!geometryPath.empty())
        glDeleteShader(geometry);
}

void Shader::use() const {
    glUseProgram(this->ID);
}

void Shader::checkErrors(unsigned int shader, std::string type) {
    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
        std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }
}

//void Shader::setInt(const std::string &name, int value) const {
//    glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
//}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setVec3(const std::string &name, float x, float y, float z) const     {
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}


