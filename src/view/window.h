#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

class Shader;
class Scene;
class Texture;

class Window {
    private:
        Window(); //private constructor for singleton design pattern
        ~Window() = default;

    public:
        Texture* tex; // TODO: remove (this is leaked memory) -- only for testing

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

        /* PRIVATE MEMBERS */
        GLuint VAO_, VBO_, EBO_;
        glm::mat4 model_, view_, projection_;

        int windowId_ = -1;
        int windowWidth_ = 0;
        int windowHeight_ = 0;
        Shader* shader_;
        Scene* scene_;
};

#endif // WINDOW_H