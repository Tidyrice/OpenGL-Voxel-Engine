#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

class Camera;

class Scene {
    public:
        Scene() = default; //subclass MUST initialize camera_ in its constructor
        virtual ~Scene() = 0;

        void Update(); //called every frame

        virtual glm::mat4 GetModelMatrix() const; //temporary. Need to embed this information in data sent to Window somehow for each block
        glm::mat4 GetViewMatrix() const; //we can return by value because of RVO (copy elision)
        glm::mat4 GetProjectionMatrix() const;

        virtual void HandleNormalKeys(unsigned char key, int x, int y) = 0;
        virtual void HandleMouseMovement(int x, int y) = 0;


    protected:
        virtual void UpdatePerFrame() = 0; //children overrides this. Called in Update()
        float GetDeltaTimeMs() const;

        GLuint VAO_, VBO_, EBO_;
        glm::mat4 model_; //model matrix
        std::unique_ptr<Camera> camera_;
};

#endif // SCENE_H
