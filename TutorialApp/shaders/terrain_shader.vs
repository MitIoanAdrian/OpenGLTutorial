#version 330 core

in vec3 Position;
in vec2 UV;
in vec3 Normal;

out vec2 TexCoords;
out float FragHeight;
out vec3 FragNormal;

uniform mat4 MVP;

void main(){
	
	gl_Position = MVP * vec4(Position.xy, Position.z * 150.0, 1.0);
	TexCoords = UV * 20.0;
	FragHeight = Position.z;
	FragNormal = Normal;
}
