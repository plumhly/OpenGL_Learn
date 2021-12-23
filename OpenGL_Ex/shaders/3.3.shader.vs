#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 ourColor;
layout (location = 2) in vec2 aTextCoord;

out vec3 vertexColor;
out vec2 TextCoord;

void main(){
    gl_Position = vec4(aPos, 1.0);
    vertexColor = ourColor;
    TextCoord = vec2(aTextCoord.x, aTextCoord.y);
}
