#version 330 core

in vec2 Position;

uniform mat4 MVP;

void main()
{
	gl_Position = MVP * vec4(Position.xy, 20.0, 1.0);
}
