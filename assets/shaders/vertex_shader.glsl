#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTextureCoords;
  
out vec3 color; // output color to fragment shader
out vec2 textureCoords; // output texture coordinates to fragment shader

void main()
{
    gl_Position = vec4(aPos, 1.0);
    color = aColor;
    textureCoords = aTextureCoords;
}
