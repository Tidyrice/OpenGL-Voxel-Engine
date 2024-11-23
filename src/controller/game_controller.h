#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "controller.h"

class GameController : public Controller {
    public:
    
    private:
        void HandleNormalKeys(unsigned char key, int x, int y) override;
        void HandleSpecialKeys(int key, int x, int y) override;
};

#endif // GAME_CONTROLLER_H