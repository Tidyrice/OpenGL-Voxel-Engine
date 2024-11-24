#ifndef SCENE_H
#define SCENE_H

#include <memory>

class Camera;

class Scene {
    public:
        Scene();
        virtual ~Scene() = 0;

        virtual void HandleRenderScene() = 0;
        // void UpdateCamera

    private:
        std::unique_ptr<Camera> camera;
};

#endif // SCENE_H
