#ifndef __EXPORTERSTRUCT_H__
#define __EXPORTERSTRUCT_H__
#include <fbxsdk.h>

#include <math.h>
#include <iostream>
#include <vector>
#include <unordered_map>

//
// Contain the structs used for skeleton animation.
//

struct Keyframe
{
	FbxLongLong FrameNum;
	FbxAMatrix GlobalTransform;
	Keyframe* Next;
};

struct Joint
{
	std::string Name;
	int32_t ParentIndex;
	FbxAMatrix GlobalBindposeInverse;
	Keyframe* Animation;
	FbxNode* Node;

	Joint() :
		Node(nullptr),
		Animation(nullptr)
	{
		GlobalBindposeInverse.SetIdentity();
		ParentIndex = -1;
	}

	~Joint()
	{
		while (Animation)
		{
			Keyframe* temp = Animation->Next;
			delete Animation;
			Animation = temp;
		}
	}
};

struct Skeleton
{
	std::vector<Joint> Joints;
};

struct BlendingIndexWeightPair
{
	uint32_t BlendingIndex;
	float BlendingWeight;
};

struct Vec3
{
	float x;
	float y;
	float z;
};

// FBX referes to each vertex with a control point
// one joint affects 4 control points
struct ControlPoint
{
	Vec3 Position;
	std::vector<BlendingIndexWeightPair> BlendingInfo;

	ControlPoint()
	{
		BlendingInfo.reserve(4);
	}
};

#endif // ! __EXPORTERSTRUCT_H__