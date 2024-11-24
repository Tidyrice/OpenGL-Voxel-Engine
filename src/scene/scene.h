#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <glm/glm.hpp>

class Camera;

class Scene {
    public:
        Scene();
        virtual ~Scene() = 0;

        virtual void HandleWKeyPress() = 0;
        virtual void HandleAKeyPress() = 0;
        virtual void HandleSKeyPress() = 0;
        virtual void HandleDKeyPress() = 0;

        // Window interface methods
        glm::mat4 GetViewMatrix() const;

    protected:
        std::unique_ptr<Camera> camera;
};

#endif // SCENE_H
