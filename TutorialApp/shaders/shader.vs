#version 330 core

layout (location = 0) in vec2 Position;
layout (location = 1) in vec3 Color;

uniform vec2 uOffset;

out vec3 vColor;

void main()
{
    gl_Position = vec4(Position.xy + uOffset, 0.0, 1.0);
    vColor = Color;
}
