#version 300 es

precision highp float;

in vec2 TexCoord;
in vec3 FragPos;

out vec4 FragColor;

void main() {
    FragColor = vec4(1.0, 1.0, 0.0f, 1.0f);
}