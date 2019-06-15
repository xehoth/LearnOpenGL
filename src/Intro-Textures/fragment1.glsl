#version 410 core
out vec4 color;

in vec3 fCol;
in vec2 fTexCoords;

// texture sampler
uniform sampler2D texture1;

uniform float r;

void main() {
    color = texture(texture1, fTexCoords) * vec4(fCol, 1.0) * r;
}