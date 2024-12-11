#include <glad/glad.h>
#include "texture.h"
#include <iostream>
#include <stb_image.h>
#include "shader.h"

Texture::Texture(const std::string& texture_path, GLenum texture_type, GLenum slot) : type_{texture_type}
{
    unsigned char* data = stbi_load(texture_path.c_str(), &width_, &height_, &nr_channels_, 0);
    if (!data) {
        std::cerr << "Texture::Texture(): failed to load texture" << std::endl;
    }

    glGenTextures(1, &id_);
    glActiveTexture(slot);
    glBindTexture(type_, id_);
    
    glTexParameteri(type_, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(type_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(type_, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(type_, GL_TEXTURE_WRAP_T, GL_REPEAT);

    if (nr_channels_ == 3) {
        glTexImage2D(type_, 0, GL_RGB, width_, height_, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }
    else if (nr_channels_ == 4) {
        glTexImage2D(type_, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    }
    else {
        std::cerr << "Texture::Texture(): unsupported number of channels" << std::endl;
    }
    glGenerateMipmap(type_);

    stbi_image_free(data);

    glBindTexture(type_, 0);
}

void
Texture::AssignTextureUnit(Shader* shader, const std::string& uniform_name, GLuint unit)
{
    GLuint texture_uniform = glGetUniformLocation(shader->GetShaderId(), uniform_name.c_str());
    shader->UseShader();
    glUniform1i(texture_uniform, unit);
}

void
Texture::Bind()
{
    glBindTexture(type_, id_);
}

void
Texture::Unbind()
{
    glBindTexture(type_, 0);
}

GLuint
Texture::GetTextureId() const
{
    return id_;
}
