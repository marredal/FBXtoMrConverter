#version 420

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec3 TexCoordsAlpha;
layout(location = 3) in vec4 JointIndex;
layout(location = 4) in vec4 JointWeight;

out vec3 Normal1;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

uniform mat4 Joints[4];

void main()
{
	vec4 newPos;
	vec4 newNormal;
	int index;

	vec4 normalizedJointWeight = normalize(JointWeight);

	// Joint 1
	index = int(JointIndex.x);
	newPos = (Joints[index] * vec4(Position, 1.0)) * normalizedJointWeight.x;
	newNormal = (Joints[index] * vec4(Normal, 0.0)) * normalizedJointWeight.x;

	// Joint 2
	index = int(JointIndex.y);
	newPos = (Joints[index] * vec4(Position, 1.0)) * normalizedJointWeight.y + newPos;
	newNormal = (Joints[index] * vec4(Normal, 0.0)) * normalizedJointWeight.y + newNormal;

	// Joint 3
	index = int(JointIndex.z);
	newPos = (Joints[index] * vec4(Position, 1.0)) * normalizedJointWeight.z + newPos;
	newNormal = (Joints[index] * vec4(Normal, 0.0)) * normalizedJointWeight.z + newNormal;

	// Joint 4
	index = int(JointIndex.w);
	newPos = (Joints[index] * vec4(Position, 1.0)) * normalizedJointWeight.w + newPos;
	newNormal = (Joints[index] * vec4(Normal, 0.0)) * normalizedJointWeight.w + newNormal;

	newNormal = normalize(newNormal);
	Normal1 = newNormal.xyz;

	gl_Position = P * V * M * vec4(newPos.xyz, 1.0);
}