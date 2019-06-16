#version 410 core
layout(location = 0) in vec3 inPos;
layout(location = 1) in vec2 inTexCoords;

uniform mat4 trans;
out vec2 fTexCoords;

void main() {
    gl_Position = trans * vec4(inPos, 1.0);
    fTexCoords = inTexCoords;
}