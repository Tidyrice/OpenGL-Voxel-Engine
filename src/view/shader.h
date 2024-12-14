#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glm/glm.hpp>
#include <glfw/glfw3.h>

class Shader {
    public:
        Shader(std::string vertex_shader_path, std::string fragment_shader_path);
        void UseShader() const;
        GLuint GetShaderId() const;

        void SetMat4(const std::string &name, const glm::mat4 &mat) const;

    private:
        void InitializeShaders(const char* vertex_shader_src, const char* fragment_shader_src);
        std::string ReadFile(std::string filename);
        GLuint shader_id_;
};

#endif // SHADER_H