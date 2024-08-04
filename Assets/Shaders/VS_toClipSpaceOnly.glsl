#version 450

uniform mat4 mvpMatrix;

layout (location = 0) in vec4 vertexPosition;

void main() {
    vec4 clip_position = vertexPosition * mvpMatrix; // post multiplication cause of layout
    gl_Position = clip_position;
}
