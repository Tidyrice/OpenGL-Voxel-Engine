#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "scene.h"

class GameScene : public Scene {
    public:
        GameScene();
        ~GameScene() = default;

        void HandleWKeyPress() override;
        void HandleAKeyPress() override;
        void HandleSKeyPress() override;
        void HandleDKeyPress() override;

    private:
        void UpdatePerFrame() override;
};

#endif // GAME_SCENE_H
