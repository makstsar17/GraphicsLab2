//
// Created by makstsar on 25.11.2021.
//

#include "../include/Camera.h"
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : position(position), world_up(up), yaw(yaw), pitch(pitch),
        front(glm::vec3(0.f, 0.f, -1.f)), movement_speed(SPEED), mouse_sensitivity(SENSITIVITY), zoom(ZOOM){
    this->update_camera_vectors();
}

void Camera::update_camera_vectors() {
    glm::vec3 direction;
    direction.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    direction.y = sin(glm::radians(this->pitch));
    direction.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

    this->front = glm::normalize(direction);
    this->right = glm::normalize(glm::cross(this->front, this->world_up));//???????// normalize(cross(worldUp, direction))
//    this->right = glm::normalize(glm::cross(this->world_up, direction));
    this->up = glm::normalize(glm::cross(this->right, this->front));      //???????// cross(direction, right)
//    this->up = glm::normalize(glm::cross(direction, this->right));
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(this->position, this->position + this->front, this->up);
}

void Camera::process_keyboard(Camera_Movement direction, float deltaTime) {
    auto velocity = this->movement_speed * deltaTime;
    if(direction == FORWARD)
        this->position += this->front * velocity;
    if(direction == BACKWARD)
        this->position -= this->front * velocity;
    if(direction == LEFT)
        this->position -= this->right * velocity;
    if(direction == RIGHT)
        this->position += this->right * velocity;
}

void Camera::process_mouse_movement(float x_offset, float y_offset, bool constrainPitch) {
    x_offset *= this->mouse_sensitivity;
    y_offset *= this->mouse_sensitivity;

    this->yaw += x_offset;
    this->pitch += y_offset;

    if (constrainPitch){
        if(this->pitch > 89.f)
            this->pitch = 89.f;
        if(this->pitch < -89.f)
            this->pitch = -89.f;
    }

    this->update_camera_vectors();
}

void Camera::process_mouse_scroll(float y_offset) {
    if(this->zoom >= 1.f && this->zoom <= 45.f)
        this->zoom -= y_offset;
    if(this->zoom <= 1.f)
        this->zoom = fabs(1);
    if(this->zoom >= 45.f)
        this->zoom = 45.f;
}
