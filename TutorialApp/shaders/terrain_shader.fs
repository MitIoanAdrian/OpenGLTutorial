#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
in vec2 SplatCoords;
in vec3 FragNormal;
in float FragHeight;

uniform sampler2D Texture0;
uniform sampler2D Texture1;
uniform sampler2D Texture2;
uniform sampler2D Texture3;
uniform sampler2D SplatMapTexture;

void main(){
	vec4 grass = texture(Texture0, TexCoords).rgba;
	vec4 rock1 = texture(Texture1, TexCoords).rgba;
	vec4 rock2 = texture(Texture2, TexCoords).rgba;
    vec4 snow = texture(Texture3, TexCoords).rgba;

	vec4 splat = texture(SplatMapTexture, SplatCoords);
   
    float a = FragHeight;
    
	vec4 terrain = mix(snow, rock2, splat.b);
	terrain = mix(terrain, rock1, splat.g);
	terrain = mix(terrain, grass, splat.r);

	FragColor = vec4(terrain);
}
