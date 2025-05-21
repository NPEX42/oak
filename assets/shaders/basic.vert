#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aUV0;
layout(location = 2) in vec4 aColor;

out vec2 vUV0;
out vec4 vColor;

void main() {
    gl_Position = vec4(aPosition, 1.0);
    //vUV0 = aUV0;
    vColor = aColor;
}