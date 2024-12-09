#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/freeglut.h>

class Shader;

class Texture {
    public:
        Texture(const std::string& texture_path, GLenum texture_type, GLenum slot);
        ~Texture() = default;

        void AssignTextureUnit(Shader* shader, const std::string& uniform_name, GLuint unit);
        void Bind();
        void Unbind();

        GLuint GetTextureId() const;

    private:
        GLuint id_;
        GLenum type_;
        int width_, height_, nr_channels_;
};

#endif // TEXTURE_H
