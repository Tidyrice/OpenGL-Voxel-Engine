#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera {
    public:
        Camera(float speed, float sensitity);
        ~Camera() = default;

        glm::mat4 GetViewMatrix();
        glm::mat4 GetProjectionMatrix(int width, int height);

        void MoveForward();
        void MoveBackward();
        void MoveLeft();
        void MoveRight();
        void MoveUp();
        void MoveDown();
        void HandleMouseMovement(double x, double y);

    private:
        void UpdateCameraVectors();
        float GetDeltaTime() const;
        float GetNormalizedCameraSpeed() const; //normalizes camera speed based on the current frame rate (delta time)
        void PrintCameraVectors() const;

        float speed_;
        float sensitivity_;

        glm::vec3 camera_pos_;
        glm::vec3 camera_front_; // points the direction camera is facing
        glm::vec3 camera_up_ = glm::vec3(0.0f, 1.0f, 0.0f); // the up vector of the camera
        
        float yaw_; // yaw zero points to the right
        float pitch_;

        bool first_mouse_movement_ = true;
        double last_x_; // previous x position for the mouse
        double last_y_; // previous y position for the mouse
};

#endif // CAMERA_H