#version 330

layout(location = 0) out vec4 oColor;

in vec4 vColor;
in vec2 vUV0;

void main() {
    oColor = vColor;
}