#version 410 core
in vec3 col;
out vec4 color;
uniform float r;

void main() {
    color = vec4(col * r, 1.0);
}