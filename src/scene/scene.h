#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

class Camera;

class Scene {
    public:
        Scene();
        virtual ~Scene() = 0;

        const virtual glm::mat4& GetModelMatrix() const; //temporary. Need to embed this information in data sent to Window somehow for each block
        const glm::mat4& GetViewMatrix() const;
        const glm::mat4& GetProjectionMatrix() const;

        virtual void HandleWKeyPress() = 0;
        virtual void HandleAKeyPress() = 0;
        virtual void HandleSKeyPress() = 0;
        virtual void HandleDKeyPress() = 0;


    protected:
        float GetDeltaTime() const;

        GLuint VAO_, VBO_, EBO_;
        glm::mat4 model_ = glm::mat4(1.0f); //model matrix
        std::unique_ptr<Camera> camera;
};

#endif // SCENE_H
