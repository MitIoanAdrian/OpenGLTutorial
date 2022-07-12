#version 330 core

out vec4 FragColor;

in vec3 vColor;

void main()
{
    FragColor = vec4(vColor.x, vColor.y, vColor.z, 0.0);
}
