#ifndef __SKELETONANIMATION_H__
#define __SKELETONANIMATION_H__
#define FBXSDK_SHARED

#include "ExporterStruct.h"

class SkeletonAnimation
{
public:
	SkeletonAnimation();
	virtual ~SkeletonAnimation();
	void Init();
	void Shutdown();
	void GetSkeleton();
	void Export();

private:
	FbxAMatrix GeometryTransformation(FbxNode* node);
	void SkeletonHierachyRecursive(FbxNode* node, int index, int parentIndex);
	void SkeletonHierachy(FbxNode* node);
	uint32_t FindJointIndex(const std::string& name);
	void FixControlPoints(FbxNode* node);
	void SkeletonJointsAndAnimations(FbxNode* node);
	void CheckMesh(FbxNode* node);
	void GetAnimation();
	



private:
	FbxManager* m_Manager;
	FbxScene* m_Scene;
	FbxImporter* m_Importer;
	Skeleton m_Skeleton;
	std::unordered_map<uint32_t, ControlPoint*>m_ControlPoints;
	bool m_HasAnimation;

};

#endif