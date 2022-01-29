#version 410 core

in vec2 texCoords;
uniform sampler2D texture1;

out vec4 fragColor;

void main() {
    fragColor = vec4(vec3(1.0 - texture(texture1, texCoords)), 1.0);
}