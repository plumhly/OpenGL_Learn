#version 410 core

in vec2 texCoords;
uniform sampler2D texture1;

out vec4 fragColor;

void main() {
    fragColor = texture(texture1, texCoords);
    float average = 0.2126 * fragColor.r + 0.7152 * fragColor.g + 0.0722 * fragColor.b;
    fragColor = vec4(average, average, average, 1.0);
}