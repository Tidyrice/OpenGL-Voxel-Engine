#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <GL/freeglut.h>
#include <glm/glm.hpp>

class Shader;
class Scene;
class Texture;

class Window {
    public:
        Texture* tex; // TODO: remove (this is leaked memory) -- only for testing

        static Window* GetActiveWindow(Window* instance = nullptr);

        Window(int w, int h, int pos_x, int pos_y, std::string window_name, Scene* s);
        ~Window() = default;

        void InitializeBuffers();
        void RegisterWindowCallbacks();

        inline void SetShader(Shader* s) { shader_ = s; }
        inline void SetScene(Scene* s) { scene_ = s; }

        inline int GetWindowWidth() const { return window_width_; }
        inline int GetWindowHeight() const { return window_height_; }

        inline float GetDeltaTimeMs() const { return delta_time_; }

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

        const glm::mat4 GetModelMatrix() const;
        const glm::mat4 GetViewMatrix() const;
        const glm::mat4 GetProjectionMatrix() const;

        void UpdateDeltaTime();

        /* PRIVATE MEMBERS */
        GLuint VAO_, VBO_, EBO_;
        Shader* shader_;
        Scene* scene_;

        int window_id_ = -1;
        int window_width_ = 0;
        int window_height_ = 0;
        float delta_time_ = 0.0f;
        float last_frame_ = 0.0f;
};

#endif // WINDOW_H