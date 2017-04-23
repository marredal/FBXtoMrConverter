#version 420

uniform sampler2D DiffuseMap;
in vec3 TexCoords1;
out vec4 FragColor;




void main()
{
	vec3 col = texture2D(DiffuseMap, TexCoords1.xy).xyz;

	FragColor = vec4(col, 1);

}