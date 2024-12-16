#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Camera;

class Scene {
    public:
        Scene() = default; //subclass MUST initialize camera_ in its constructor
        virtual ~Scene() = 0;

        void Update(); //called every frame
        virtual GLuint GenerateArrayTexture() = 0;

        virtual glm::mat4 GetModelMatrix() const; //temporary. Need to embed this information in data sent to Window somehow for each block
        glm::mat4 GetViewMatrix() const; //we can return by value because of RVO (copy elision)
        glm::mat4 GetProjectionMatrix() const;

        inline GLuint GetVAO() const { return VAO_; }
        inline GLuint GetVBO() const { return VBO_; }
        inline GLuint GetEBO() const { return EBO_; }

        virtual void HandleNormalKeys(int key, int action) = 0;
        virtual void HandleMouseMovement(double x, double y) = 0;


    protected:
        virtual void UpdatePerFrame() = 0; //children overrides this. Called in Update()
        float GetDeltaTime() const;

        GLuint VAO_, VBO_, EBO_;
        glm::mat4 model_; //model matrix
        std::unique_ptr<Camera> camera_;
};

#endif // SCENE_H
