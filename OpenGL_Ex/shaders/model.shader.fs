
#version 410 core

out vec4 FragColor;

in vec2 textureCoords;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

void main() {
    FragColor = texture(texture_diffuse1, textureCoords) + texture(texture_specular1, textureCoords);
}