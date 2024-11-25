#ifndef WINDOW_H
#define WINDOW_H

#include <string>

class Scene;

class Window {
    private:
        Window() = default; //private constructor for singleton design pattern
        ~Window() = default;

    public:
        Window(Window const&) = delete;
        Window(Window&&) = delete;
        Window& operator=(Window const&) = delete;
        Window& operator=(Window&&) = delete;

        static Window& getInstance() { //Meyer's singleton
            static Window instance;
            return instance;
        }

        //pos_x and pos_y are the position of the window on the screen
        //this method should only be called once
        void CreateAndInitializeWindow(int w, int h, int pos_x, int pos_y, std::string window_name, Scene* s);
        void RegisterWindowCallbacks();

        inline void SetScene(Scene* s) { scene = s; }

        void Clear();

    private:
        static void RenderSceneCallback();
        void HandleRenderScene();

        static void WindowResizeCallback(int w, int h);
        void HandleResize(int w, int h);

        int windowId = -1;
        int windowWidth = 0;
        int windowHeight = 0;
        Scene* scene;
};

#endif // WINDOW_H