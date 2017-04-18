#ifndef __SKELETONANIMATION_H__
#define __SKELETONANIMATION_H__
#define FBXSDK_SHARED

#include "SkeletonStruct.h"

class Exporter
{
public:
	Exporter();
	virtual ~Exporter();
	void Init();
	void Shutdown();
	void GetSkeleton();

private:
	FbxAMatrix GeometryTransformation(FbxNode* node);
	void SkeletonHierachyRecursive(FbxNode* node, int index, int parentIndex);
	void SkeletonHierachy(FbxNode* node);
	uint32_t FindJointIndex(const std::string& name);
	void fixControlPoints(FbxNode* node);
	void SkeletonJointsAndAnimations(FbxNode* node);
	void checkMesh(FbxNode* node);
	void GetAnimation();


private:
	FbxManager* m_Manager;
	FbxScene* m_Scene;
	FbxImporter* m_Importer;
	Skeleton m_Skeleton;
	std::unordered_map<uint32_t, ControlPoint*>m_ControlPoints;

};

#endif