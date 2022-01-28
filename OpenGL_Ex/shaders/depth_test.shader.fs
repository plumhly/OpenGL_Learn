#version 410 core

out vec4 fragColor;

in vec2 texCoords;

uniform sampler2D texture1;

void main() {
    vec4 color = texture(texture1, texCoords);
    if(color.a < 0.1){
        discard;
    }
    fragColor = color;
}