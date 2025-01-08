#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "window.h"
#include <iostream>

Camera::Camera(float speed, float sensitity, glm::vec3 position, float yaw, float pitch)
    : speed_{speed}, sensitivity_{sensitity}, camera_pos_{position}, yaw_{yaw}, pitch_{pitch}
{
    UpdateCameraVectors();
}

glm::mat4
Camera::GetViewMatrix()
{
    return glm::lookAt(camera_pos_, camera_pos_ + camera_front_, camera_up_);
}

glm::mat4
Camera::GetProjectionMatrix(int width, int height)
{
    return glm::perspective(glm::radians(fov_), (float)width / (float)height, near_, far_);
}

void
Camera::MoveForward()
{
    move_direction_horizontal_ += glm::normalize(glm::vec3(camera_front_.x, 0.0f, camera_front_.z));
}

void
Camera::MoveBackward()
{
    move_direction_horizontal_ -= glm::normalize(glm::vec3(camera_front_.x, 0.0f, camera_front_.z));
}

void
Camera::MoveLeft()
{
    move_direction_horizontal_ -= glm::normalize(glm::cross(camera_front_, camera_up_));
}

void
Camera::MoveRight()
{
    move_direction_horizontal_ += glm::normalize(glm::cross(camera_front_, camera_up_));
}

void
Camera::MoveUp()
{
    move_direction_vertical_ += glm::normalize(camera_up_);
}

void
Camera::MoveDown()
{
    move_direction_vertical_ -= glm::normalize(camera_up_);
}

void
Camera::MakeMove()
{
    //need to check if we moved, otherwise glm::normalize has weird behaviour with zero vectors
    static const float epsilon = 0.0001f;
    if (glm::length(move_direction_horizontal_) > epsilon) {
        camera_pos_ += glm::normalize(move_direction_horizontal_) * GetNormalizedCameraSpeed();
    }
    if (glm::length(move_direction_vertical_) > epsilon) {
        camera_pos_ += glm::normalize(move_direction_vertical_) * GetNormalizedCameraSpeed();
    }

    //check for NAN
    if (glm::any(glm::isnan(camera_pos_))) {
        std::cerr << "Camera::MakeMove(): camera_pos_ is nan" << std::endl;
        exit(-1);
    }

    move_direction_horizontal_ = glm::vec3(0.0f);
    move_direction_vertical_ = glm::vec3(0.0f);

    UpdateCameraVectors();
}

void
Camera::HandleMouseMovement(double x, double y)
{
    if (first_mouse_movement_) { //this check is needed otherwise camera will jump when mouse first comes into frame
        last_x_ = x;
        last_y_ = y;
        first_mouse_movement_ = false;
        return;
    }

    //difference in mouse position
    float x_offset = (x - last_x_) * sensitivity_;
    float y_offset = (last_y_ - y) * sensitivity_; // reversed since y-coordinates range from bottom to top

    last_x_ = x;
    last_y_ = y;

    //update camera angles
    yaw_ += x_offset;
    pitch_ += y_offset;

    //check bounds for pitch
    if (pitch_ > 89.0f) {
        pitch_ = 89.0f;
    }
    if (pitch_ < -89.0f) {
        pitch_ = -89.0f;
    }

    UpdateCameraVectors();
}

void
Camera::UpdateCameraVectors()
{
    //declaring a new variable to avoid dirty reads (happens if we modify components of camera_front_ directly)
    glm::vec3 front;
    front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front.y = sin(glm::radians(pitch_));
    front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    camera_front_ = glm::normalize(front);

    // PrintCameraVectors();
}

float
Camera::GetDeltaTime() const
{
    return Window::GetActiveWindow()->GetDeltaTime();
}

float
Camera::GetNormalizedCameraSpeed() const
{
    return speed_ * GetDeltaTime();
}

void
Camera::PrintCameraVectors() const
{
    std::cout << "--- Camera::PrintCameraVectors() ---" << std::endl;
    std::cout << "Camera Position: (" << camera_pos_.x << ", " << camera_pos_.y << ", " << camera_pos_.z << ")" << std::endl;
    std::cout << "Camera Front: (" << camera_front_.x << ", " << camera_front_.y << ", " << camera_front_.z << ")" << std::endl;
    std::cout << "Yaw: " << yaw_ << std::endl;
    std::cout << "Pitch: " << pitch_ << std::endl;
}