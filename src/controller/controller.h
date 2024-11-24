#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>

class Window;
class Scene;

class Controller {
    public:
        Controller(Scene* s): scene{s} {};
        virtual ~Controller() = default;

        inline static void SetActiveControllerInstance(Controller* c)
        {
            active_controller_instance = c;
        }

        static void ProcessNormalKeysCallback(unsigned char key, int x, int y);
        static void ProcessSpecialKeysCallback(int key, int x, int y);

    private:
        static Controller* active_controller_instance;
        virtual void HandleNormalKeys(unsigned char key, int x, int y) = 0;
        virtual void HandleSpecialKeys(int key, int x, int y) = 0;

        Scene* scene;
};

#endif // CONTROLLER_H