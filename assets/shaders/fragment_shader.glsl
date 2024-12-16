#version 330 core
out vec4 FragColor;

in vec2 textureCoords;
flat in int textureLayer;

uniform sampler2DArray textureArray;

void main()
{
    FragColor = texture(textureArray, vec3(textureCoords, textureLayer));
}
