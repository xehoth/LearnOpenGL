#version 410 core
out vec4 color;

in vec2 fTexCoords;

// texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
    color = mix(texture(texture1, fTexCoords), texture(texture2, fTexCoords), 0.4);
}