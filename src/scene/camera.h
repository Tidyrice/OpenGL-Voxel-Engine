#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera {
    public:
        Camera() = default;
        ~Camera() = default;

        glm::mat4 GetViewMatrix();

        void MoveForward();
        void MoveBackward();
        void MoveLeft();
        void MoveRight();

    private:
        const float cameraSpeed = 0.05f;
        glm::vec3 camera_pos = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 camera_front = glm::vec3(0.0f, 0.0f, -1.0f); //direction camera is looking
        glm::vec3 camera_up = glm::vec3(0.0f, 1.0f, 0.0f);
};

#endif // CAMERA_H