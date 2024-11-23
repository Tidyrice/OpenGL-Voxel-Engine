#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "window.h"
#include <memory>

class Controller {
    public:
        Controller() = default;
        virtual ~Controller() = default;

        static void SetActiveControllerInstance(Controller* controller);

        //these functions will throw if no active controller is set
        static void ProcessNormalKeysCallback(unsigned char key, int x, int y);
        static void ProcessSpecialKeysCallback(int key, int x, int y);

    private:
        static Controller* active_controller_instance;
        virtual void HandleNormalKeys(unsigned char key, int x, int y) = 0;
        virtual void HandleSpecialKeys(int key, int x, int y) = 0;
};

#endif // CONTROLLER_H