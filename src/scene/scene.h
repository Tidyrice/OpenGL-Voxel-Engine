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

        const virtual glm::mat4& GetModelMatrix() const; //temporary. Need to embed this information in data sent to Window somehow for each block
        const glm::mat4& GetViewMatrix() const;
        const glm::mat4& GetProjectionMatrix() const;

        virtual void HandleWKeyPress() = 0;
        virtual void HandleAKeyPress() = 0;
        virtual void HandleSKeyPress() = 0;
        virtual void HandleDKeyPress() = 0;


    protected:
        virtual void UpdatePerFrame() = 0; //children overrides this. Called in Update()
        float GetDeltaTimeMs() const;

        GLuint VAO_, VBO_, EBO_;
        glm::mat4 model_; //model matrix
        std::unique_ptr<Camera> camera_;
};

#endif // SCENE_H
