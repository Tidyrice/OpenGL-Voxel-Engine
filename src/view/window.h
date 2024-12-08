#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <GL/freeglut.h>

class Shader;
class Scene;

class Window {
    private:
        Window(); //private constructor for singleton design pattern
        ~Window() = default;

    public:
        static Window& getInstance() { //Meyer's singleton
            static Window instance;
            return instance;
        }

        void CreateAndInitializeWindow(int w, int h, int pos_x, int pos_y, std::string window_name, Scene* s);
        void InitializeBuffers();
        void RegisterWindowCallbacks() const;

        inline void SetShader(Shader* s) { shader_ = s; }
        inline void SetScene(Scene* s) { scene_ = s; }

        void Clear();

    private:
        Window(Window const&) = delete;
        Window(Window&&) = delete;
        Window& operator=(Window const&) = delete;
        Window& operator=(Window&&) = delete;
        
        static void RenderSceneCallback();
        void HandleRenderScene();
        static void WindowResizeCallback(int w, int h);
        void HandleResize(int w, int h);

        GLuint VAO_, VBO_, EBO_;
        int windowId_ = -1;
        int windowWidth_ = 0;
        int windowHeight_ = 0;
        Shader* shader_;
        Scene* scene_;

        GLuint texture; // TODO: move this to a texture class
};

#endif // WINDOW_H