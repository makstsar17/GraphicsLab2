//
// Created by makstsar on 18.11.2021.
//

#ifndef LAB1_SHADER_H
#define LAB1_SHADER_H

#include <iostream>
#include <glm.hpp>

class Shader {
public:
    unsigned int ID;

    Shader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath = "");

    void use() const;

//    void setInt(const std::string& name, int value) const;

    void setMat4(const std::string& name, const glm::mat4& mat) const;

    void setVec3(const std::string& name, float x, float y, float z) const;

    void setFloat(const std::string& name, float value) const;

private:
    static void checkErrors(unsigned int shader, std::string type);
};


#endif //LAB1_SHADER_H
