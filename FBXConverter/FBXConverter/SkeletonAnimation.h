#ifndef __SKELETONANIMATION_H__
#define __SKELETONANIMATION_H__
#define FBXSDK_SHARED

#include "ExporterStruct.h"
#include "glm.hpp"
class SkeletonAnimation
{
public:
	SkeletonAnimation();
	virtual ~SkeletonAnimation();
	void GetSkeleton();
	void Export();
	void SetScene(FbxScene* scene);
	void SetBindPose(int32_t &bindPoseJointID, glm::mat4 &BindPoseMatrix);
	int32_t GetFirstKeyFrame();
	int32_t GetLastKeyFrame();
	std::vector<int32_t>GetJointID();
	std::vector<int32_t>GetParentID();
	std::vector<glm::vec3>GetTransformationMatrices();
	std::vector<glm::vec3>GetRotationMatrices();
	std::vector<glm::vec3>GetScalingMatrices();

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
	Skeleton m_Skeleton;
	int32_t m_firstFrame;
	int32_t m_lastFrame;
	glm::mat4 m_globalBindPoseMat;
	std::vector<glm::vec3> m_localTransformMat;
	std::vector<glm::vec3> m_localRotationMat;
	std::vector<glm::vec3> m_localScaleMat;
	FbxScene* m_Scene;
	std::unordered_map<uint32_t, ControlPoint*>m_ControlPoints;
	bool m_HasAnimation;
	std::vector<int32_t> m_index;
	std::vector<int32_t> m_parentIndex;
};

#endif