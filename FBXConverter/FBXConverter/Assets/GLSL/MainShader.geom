#version 420
layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;


in vec2 TexCoord[3];


out vec3 tangent;
out mat3 TBN;
out vec2 TexCoords;

void CreateNormalMap()
{
	vec3 edge0 = gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz;
	vec3 edge0 = gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz;

	vec2 deltaUV0 = TexCoords[1] - TexCoords[0];
	vec2 deltaUV1 = TexCoords[2] - TexCoords[0];

	float f = 1.0f / (deltaUV0.x * deltaUV1.y - deltaUV1.x * deltaUV0.y);

	tangent.x = f * (deltaUV1.y * edge0.x - deltaUV0.y * edge1.x);
	tangent.y = f * (deltaUV1.y * edge0.y - deltaUV0.y * edge1.y);
	tangent.z = f * (deltaUV1.y * edge0.z - deltaUV0.y * edge1.z);
	tangent = normalize(tangent);

	bitangent.x = f * (-deltaUV1.x * edge0.x + deltaUV0.x * edge1.x);
	bitangent.y = f * (-deltaUV1.x * edge0.y + deltaUV0.x * edge1.y);
	bitangent.z = f * (-deltaUV1.x * edge0.z + deltaUV0.x * edge1.z);
	bitangent = normalize(bitangent);

	
	vec3 T = normalize(vec3(Model * vec4(tangent, 1.0)));
	vec3 B = normalize(vec3(Model * vec4(bitangent, 1.0)));
	vec3 N = normalize(vec3(Model * vec4(createNormal())));

	TBN = mat3(T, B, N);
}


void createGeometry()
{
	
		for(int i = 0; i < 3; i++)
		{
			gl_Position = gl_in[i].gl_Position;
			TexCoords = TexCoord[i];
			EmitVertex();
		}
		EndPrimitive();

}

void main()
{
	createGeometry();
}