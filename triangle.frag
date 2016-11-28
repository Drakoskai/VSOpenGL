#version 450

#define FRAG_COLOR  0

precision highp float;
precision highp int;
layout(std140, column_major) uniform;
layout(std430, column_major) buffer;

layout (location = 0) in vec3 interpolatedColor;

layout (location = FRAG_COLOR) out vec4 outputColor;

void main() {
    outputColor = vec4(interpolatedColor, 1.0);
}
