#ifndef WINDOW_H
#define WINDOW_H

#include <string>

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
        void CreateAndInitializeWindow(int w, int h, int pos_x, int pos_y, std::string window_name);

        void Clear();

    private:
        void RegisterCallbacks();

        static void RenderSceneCallback();
        void HandleRenderScene();

        static void WindowResizeCallback(int w, int h);
        void HandleResize(int w, int h);

        int windowId;
};

#endif // WINDOW_H