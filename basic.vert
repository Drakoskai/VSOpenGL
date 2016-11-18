#version 400
#define POSITION    0
#define TRANSFORM0  1
#define BLOCK       0

precision highp float;
precision highp int;

layout(std140, column_major) uniform;
layout(std430, column_major) buffer;

layout (location = POSITION) in vec3 position;

layout (binding = TRANSFORM0) uniform Transform
{
    mat4 modelToClipMatrix;
} transform;

// Outgoing color.
layout (location = 0) out vec3 interpolatedColor;

void main() {
    gl_Position = transform.modelToClipMatrix * vec4(position, 1.0);
    interpolatedColor = vec3(clamp(position, 0, 1));
}