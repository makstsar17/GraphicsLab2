//
// Created by makstsar on 25.11.2021.
//

#ifndef GRAPHICSLAB2_CAMERA_H
#define GRAPHICSLAB2_CAMERA_H

#include <glm/glm.hpp>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float YAW = -90.f;
const float PITCH = 0.f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.f;

class Camera {
public:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 world_up;

    float yaw;
    float pitch;

    float movement_speed;
    float mouse_sensitivity;
    float zoom;

    Camera(glm::vec3 position = glm::vec3(0.f, 0.f, 0.f), glm::vec3 up = glm::vec3(0.f, 1.f, 0.f), float yaw = YAW, float pitch = PITCH);

    glm::mat4 getViewMatrix() const;

    void process_keyboard(Camera_Movement direction, float deltaTime);

    void process_mouse_movement(float x_offset, float y_offset, bool constrainPitch = true);

    void process_mouse_scroll(float y_offset);

private:
    void update_camera_vectors();
};


#endif //GRAPHICSLAB2_CAMERA_H
