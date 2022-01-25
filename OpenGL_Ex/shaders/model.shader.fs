
#version 410 core

out vec4 FragColor;

in vec2 textureCoords;

uniform sampler2D texture_diffusel;

void main() {
    FragColor = texture(texture_diffusel, textureCoords);
}