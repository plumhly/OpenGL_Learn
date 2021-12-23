#version 410 core

in vec3 vertexColor;
in vec2 TextCoord;

out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
    FragColor = mix(texture(texture1, TextCoord), texture(texture2, TextCoord), 0.2);
}
