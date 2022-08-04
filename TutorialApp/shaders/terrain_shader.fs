#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragNormal;
in float FragHeight;

uniform sampler2D Texture;

void main(){
	vec4 terrain = texture(Texture, TexCoords).rgba;
   
    float a = FragHeight;
    
	FragColor = vec4(terrain);
}
