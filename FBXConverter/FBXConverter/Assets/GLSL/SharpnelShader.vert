#version 420

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 TexCoords;

out vec3 TexCoords1;
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

void main()
{
	//mat4 PV = P;
	//gl_Position = MVP * vec4(Position, 1.0f);
	gl_Position =  vec4(Position, 1.0f);
	TexCoords1 = TexCoords;
}

