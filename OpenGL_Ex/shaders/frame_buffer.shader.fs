#version 410 core

in vec2 texCoords;
uniform sampler2D texture1;

out vec4 fragColor;

void main() {
    fragColor = texture(texture1, texCoords);
}