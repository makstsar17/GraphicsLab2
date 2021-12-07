cmake_minimum_required(VERSION 3.16)
project(GraphicsLab2)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/Modules")
set(CMAKE_CXX_STANDARD 20)

find_package(GLFW REQUIRED)
include_directories(${GLFW_INCLUDE_DIR})
include_directories(libs/glad)
include_directories(libs/KHR)
include_directories(libs/glm)

add_executable(GraphicsLab2 src/main.cpp libs/glad.c src/Shader.cpp include/Shader.h libs/glm/glm.hpp libs/glm/gtc/matrix_transform.hpp libs/glm/gtc/type_ptr.hpp libs/stb_image.cpp libs/stb_image.h src/elements/Figure.cpp include/elements/Figure.h src/elements/Dodecahedron.cpp include/elements/Dodecahedron.h src/elements/Octahedron.cpp include/elements/Octahedron.h src/Camera.cpp include/Camera.h src/elements/Graph.cpp include/elements/Graph.h src/GLprogram.cpp include/GLprogram.h src/elements/Elements.cpp include/elements/Elements.h)

target_link_libraries(GraphicsLab2 ${GLFW_LIBRARIES})

target_include_directories(GraphicsLab2 PRIVATE libs)
