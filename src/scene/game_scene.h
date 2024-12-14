#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "scene.h"

class GameScene : public Scene {
    public:
        GameScene();
        ~GameScene() = default;

        void HandleNormalKeys(int key, int action) override;
        void HandleMouseMovement(double x, double y) override;

    private:
        void UpdatePerFrame() override;
};

#endif // GAME_SCENE_H
