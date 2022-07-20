#version 330 core

in vec3 Position;
in vec2 UV;

uniform mat4 MVP;

out vec2 TexCoords;


void main()
{
    gl_Position = MVP * vec4(Position, 1.0);
    TexCoords = UV;
    
}
