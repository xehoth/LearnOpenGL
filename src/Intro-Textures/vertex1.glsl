#version 410 core
layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inCol;
layout(location = 2) in vec2 inTexCoords;

out vec3 fCol;
out vec2 fTexCoords;

void main() {
    gl_Position = vec4(inPos, 1.0);
    fCol = inCol;
    fTexCoords = inTexCoords;
}