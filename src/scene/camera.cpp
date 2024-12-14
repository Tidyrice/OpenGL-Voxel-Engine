#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "window.h"
#include <iostream>

Camera::Camera(float speed, float sensitity) : speed_{speed}, sensitivity_{sensitity}
{
    camera_pos_ = glm::vec3(0.0f, 0.0f, 3.0f);
    yaw_ = -90.0f;
    pitch_ = 0.0f;
}

glm::mat4
Camera::GetViewMatrix()
{
    return glm::lookAt(camera_pos_, camera_pos_ + camera_front_, camera_up_);
}

glm::mat4
Camera::GetProjectionMatrix(int width, int height)
{
    return glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
}

void
Camera::MoveForward()
{
    camera_pos_ += GetNormalizedCameraSpeed() * camera_front_;
    UpdateCameraVectors();
}

void
Camera::MoveBackward()
{
    camera_pos_ -= GetNormalizedCameraSpeed() * camera_front_;
    UpdateCameraVectors();
}

void
Camera::MoveLeft()
{
    camera_pos_ -= glm::normalize(glm::cross(camera_front_, camera_up_)) * GetNormalizedCameraSpeed();
    UpdateCameraVectors();
}

void
Camera::MoveRight()
{
    camera_pos_ += glm::normalize(glm::cross(camera_front_, camera_up_)) * GetNormalizedCameraSpeed();
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