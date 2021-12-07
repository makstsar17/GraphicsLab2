//
// Created by makstsar on 26.11.2021.
//

#ifndef GRAPHICSLAB2_GLPROGRAM_H
#define GRAPHICSLAB2_GLPROGRAM_H

#include <glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include "Camera.h"
#include "Shader.h"
#include "elements/Elements.h"

class GLprogram {
private:
    static const inline unsigned int SCR_WIDTH = 1200;
    static const inline unsigned int SCR_HEIGHT = 1200;

    Shader *shaderProgram;
    Shader *shaderProgramForPlot;
    GLFWwindow *window;
    std::vector<Elements*> elements_to_draw;

    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void processInput(GLFWwindow* window);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

public:
    inline static float deltaTime = 0.f;
    inline static float lastFrame = 0.f;

    inline static float last_x = (float)SCR_WIDTH / 2.f;
    inline static float last_y = (float)SCR_HEIGHT / 2.f;

    inline static bool first_mouse = true;

    inline static Camera *camera;

    GLprogram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const std::string& fragmentShaderPathForPlot);

    void run();

    void clear_data();

    void addElement(Elements *element);
};


#endif //GRAPHICSLAB2_GLPROGRAM_H
