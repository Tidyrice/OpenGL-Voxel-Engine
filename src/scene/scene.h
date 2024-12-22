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

        glm::mat4 GetViewMatrix() const; //we can return by value because of RVO (copy elision)
        glm::mat4 GetProjectionMatrix() const;

        virtual void HandleNormalKeys(int key, int action) = 0;
        virtual void HandleMouseMovement(double x, double y) = 0;


    protected:
        virtual void UpdatePerFrame() = 0; //children overrides this. Called in Update()
        float GetDeltaTime() const;

        GLuint VAO_, EBO_;
        GLuint pos_tex_VBO_; //holds position (vec3) and texture coordinates (vec2)
        GLuint layer_VBO_; //holds texture layer (int)
        std::unique_ptr<Camera> camera_;
};

#endif // SCENE_H
