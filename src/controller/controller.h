#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>

class Window;
class Scene;

class Controller {
    public:
        static Controller* GetActiveController(Controller* instance = nullptr);

        Controller(Scene* s): scene_{s} {};
        ~Controller() = default;

        static void ProcessNormalKeysCallback(unsigned char key, int x, int y);
        static void ProcessSpecialKeysCallback(int key, int x, int y);
        static void ProcessMouseMovementCallback(int x, int y);

    private:
        void HandleNormalKeys(unsigned char key, int x, int y) ;
        void HandleSpecialKeys(int key, int x, int y);
        void HandleMouseMovement(int x, int y);

        Scene* scene_;
};

#endif // CONTROLLER_H