#version 420

uniform sampler2D test;
uniform sampler2D t;
uniform sampler2D tx;
uniform sampler2D ty;
uniform vec3 Color;

in vec2 TexCoord;

out vec4 FragColor;


void main()
{

	
	//FragColor = vec4(Color, 0);
	FragColor = vec4(1,0,1,1) * vec4(TexCoord, 1, 0);
	//FragColor = texture2D(tx, TexCoord) * vec4(1,1,1,0);

}