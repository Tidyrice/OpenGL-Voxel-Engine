#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTextureCoords;
layout (location = 2) in int aTextureLayer;
  
out vec2 textureCoords; // output texture coordinates to fragment shader
flat out int textureLayer; // output texture layer to fragment shader (flat: prevent interpolation for discrete data)

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    textureCoords = aTextureCoords;
    textureLayer = aTextureLayer;
}
