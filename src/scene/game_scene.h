#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "scene.h"

class GameScene : public Scene {
    public:
        GameScene();
        ~GameScene() = default;

        void HandleNormalKeys(unsigned char key, int x, int y) override;
        void HandleMouseMovement(int x, int y) override;

    private:
        void UpdatePerFrame() override;
};

#endif // GAME_SCENE_H
