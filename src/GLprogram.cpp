//
// Created by makstsar on 26.11.2021.
//

#include "../include/GLprogram.h"
#include "../include/elements/Graph.h"
#include <glm/gtc/matrix_transform.hpp>
#include <typeinfo>

GLprogram::GLprogram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath, const std::string& fragmentShaderPathForPlot){

    camera = new Camera(glm::vec3(0.f, 0.f, 10.f));

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "lab2", nullptr, nullptr);
    if (window == nullptr){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    this->shaderProgram = new Shader(vertexShaderPath, fragmentShaderPath);
    this->shaderProgramForPlot = new Shader(vertexShaderPath, fragmentShaderPathForPlot);
    this->shaderProgram->use();
}

void GLprogram::run() {
    while(!glfwWindowShouldClose(window)) {
        auto currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto projection = glm::perspective(glm::radians(camera->zoom), SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 100.f);
//        this->shaderProgram->setMat4("projection", projection);

        auto view = camera->getViewMatrix();

        glm::mat4 model;
        for(auto &element: elements_to_draw){
            model = glm::mat4(1.0f);
            model = glm::translate(model, element->getWorldPosition());
            if(element->getType() == "Graph") {
                glLineWidth(1);
                this->shaderProgramForPlot->use();
                this->shaderProgramForPlot->setMat4("projection", projection);
                this->shaderProgramForPlot->setMat4("view", view);
                this->shaderProgramForPlot->setMat4("model", model);

                element->draw(this->shaderProgramForPlot);
            }
            else {
                glLineWidth(4);
                this->shaderProgram->use();
                this->shaderProgram->setMat4("projection", projection);
                this->shaderProgram->setMat4("view", view);
                this->shaderProgram->setMat4("model", model);

                element->draw(this->shaderProgram);
            }
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void GLprogram::clear_data() {
    for(auto &element: elements_to_draw)
        element->clear();
    glfwTerminate();
}

void GLprogram::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void GLprogram::processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->process_keyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->process_keyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->process_keyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->process_keyboard(RIGHT, deltaTime);
}

void GLprogram::mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    if (first_mouse){
        last_x = xpos;
        last_y = ypos;
        first_mouse = false;
    }

    auto x_offset = xpos - last_x;
    auto y_offset = last_y - ypos;

    last_x = xpos;
    last_y = ypos;

    camera->process_mouse_movement(x_offset, y_offset);
}

void GLprogram::scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    camera->process_mouse_scroll(yoffset);
}

void GLprogram::addElement(Elements *element) {
    this->elements_to_draw.push_back(element);
}
