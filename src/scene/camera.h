#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera {
    public:
        Camera() = default;
        ~Camera() = default;

        void GenerateViewMatrix();
        void GenerateProjectionMatrix(int width, int height);
        const glm::mat4& GetViewMatrix();
        const glm::mat4& GetProjectionMatrix();

        void MoveForward();
        void MoveBackward();
        void MoveLeft();
        void MoveRight();

    private:
        float GetDeltaTime() const;
        float GetNormalizedCameraSpeed() const; //normalizes camera speed based on the current frame rate (delta time)

        const float camera_speed_ = 2.5f;
        glm::vec3 camera_pos_ = glm::vec3(0.0f, 0.0f, 3.0f);
        glm::vec3 camera_target_ = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 camera_front_ = glm::normalize(camera_target_ - camera_pos_); // points the direction camera is facing
        glm::vec3 camera_up_ = glm::vec3(0.0f, 1.0f, 0.0f); // the up vector of the camera
        glm::vec3 world_up_ = glm::vec3(0.0f, 1.0f, 0.0f);

        glm::mat4 view_, projection_; //view and projection matricies
};

#endif // CAMERA_H