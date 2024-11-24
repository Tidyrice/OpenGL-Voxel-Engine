#include "camera.h"
#include <glm/gtc/type_ptr.hpp>

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(camera_pos, camera_pos + camera_front, camera_up);
}

void Camera::MoveForward()
{
    camera_pos += cameraSpeed * camera_front;
}

void Camera::MoveBackward()
{
    camera_pos -= cameraSpeed * camera_front;
}

void Camera::MoveLeft()
{
    camera_pos -= glm::normalize(glm::cross(camera_front, camera_up)) * cameraSpeed;
}

void Camera::MoveRight()
{
    camera_pos += glm::normalize(glm::cross(camera_front, camera_up)) * cameraSpeed;
}