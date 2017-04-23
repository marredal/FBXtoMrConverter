#version 420

in vec3 TexCoords1;
out vec4 FragColor;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform sampler2D DiffuseMap;


const float offset = 1.0 / 300;

const float blurr = 16;


void main()
{
	//vec3 col = texture2D(DiffuseMap, TexCoords1.xy).xyz;
	
	vec2 offsets[9] = vec2[](
		vec2(-offset, offset),
		vec2(0.0f,	  offset),
		vec2(offset,  offset),
		vec2(-offset, 0.0f),
		vec2(0.0,     0.0f),
		vec2(offset,  0.0f),
		vec2(-offset, -offset),
		vec2(0.0f,    -offset),
		vec2(offset,  -offset));
	

	float kernalB[9] = float[](
	1.0/blurr, 2.0/blurr, 1.0/blurr,
	2.0/blurr, 4.0/blurr, 2.0/blurr,
	1.0/blurr, 2.0/blurr, 1.0/blurr);

	vec3 sampleTex[9];
	for(int i =0; i<9;i++)
	{
		sampleTex[i] = vec3(texture(DiffuseMap,TexCoords1.xy +offsets[i]));
	}
	vec3 col = vec3(0.0);
	for(int i =0; i<9;i++)
	{
		col += sampleTex[i] * kernalB[i];
	}



	FragColor = vec4(col, 1);
	//FragColor = vec4(TexCoords1, 0) * vec4(1,1,1,1);

}