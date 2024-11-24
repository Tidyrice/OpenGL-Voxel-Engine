#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "scene.h"

class GameScene : public Scene {
    public:
        GameScene() = default;
        ~GameScene() = default;

        void HandleRenderScene() override;
    private:
};

#endif // GAME_SCENE_H
