#include <iostream>
#include <glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "../include/Shader.h"
#include "../include/elements/Dodecahedron.h"
#include "../include/elements/Octahedron.h"
#include "../include/Camera.h"
#include "../include/elements/Graph.h"
#include "../include/GLprogram.h"

int main() {
    GLprogram program(R"(..\shaders\shader.vs)", R"(..\shaders\shader.fs)", R"(..\shaders\shader_for_plot.fs)");
    program.addElement(new Dodecahedron());
    program.addElement(new Octahedron());
    program.addElement(new Graph([](float x, float y){return sqrt(x) + sqrt(y);},
                       0.f, 5.f, 0.f, 5.f, 0.05f));
//    program.addElement(new Graph([](float x, float y){return sin(x*x + y*y);},
//                                 -5.f, 5.f, -5.f, 5.f, 0.1f));
    program.run();
    program.clear_data();

    return 0;
}

