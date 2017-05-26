#include "SkeletonAnimation.h"



SkeletonAnimation::SkeletonAnimation()
{
	m_HasAnimation = true;

}


SkeletonAnimation::~SkeletonAnimation()
{
	// Do nothing...
}

void SkeletonAnimation::GetSkeleton()
{
	// Maybe necessary we will see
	//if (m_Skeleton.Joints.empty())
	//{
	//	m_Animation = false;
	//}	checkMesh(m_Scene->GetRootNode());
	if (m_Skeleton.Joints.empty())
		m_HasAnimation = false;

	if (m_HasAnimation)
		GetAnimation();

}

FbxAMatrix SkeletonAnimation::GeometryTransformation(FbxNode * node)
{
	const FbxVector4 translation = node->GetGeometricTranslation(FbxNode::eSourcePivot);
	const FbxVector4 rotation = node->GetGeometricRotation(FbxNode::eSourcePivot);
	const FbxVector4 scaling = node->GetGeometricScaling(FbxNode::eSourcePivot);

	FbxAMatrix temp(translation, rotation, scaling);


	return temp;
}

void SkeletonAnimation::SkeletonHierachyRecursive(FbxNode * node, int index, int parentIndex)
{
	if (node->GetNodeAttribute() && node->GetNodeAttribute()->GetAttributeType() && node->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eSkeleton)
	{
		Joint currentJoint;
		currentJoint.ParentIndex = parentIndex;
		currentJoint.Name = node->GetName();
		m_index.push_back(index);
		m_parentIndex.push_back(parentIndex);

		m_Skeleton.Joints.push_back(currentJoint);
		//std::cout << m_Skeleton.Joints[index].Name.c_str() << std::endl;


	}

	for (int i = 0; i < node->GetChildCount(); i++)
	{
		SkeletonHierachyRecursive(node->GetChild((i)), m_Skeleton.Joints.size(), index);
	}


}

void SkeletonAnimation::SkeletonHierachy(FbxNode * node)
{
	for (int i = 0; i < node->GetChildCount(0); i++)
	{
		SkeletonHierachyRecursive(node->GetChild(i), 0, -1);
	}
}

uint32_t SkeletonAnimation::FindJointIndex(const std::string & name)
{
	for (int i = 0; i < m_Skeleton.Joints.size(); i++)
	{
		if (m_Skeleton.Joints[i].Name == name)
		{
			return i;
		}
	}
}

void SkeletonAnimation::FixControlPoints(FbxNode * node)
{
	FbxMesh* currentMesh = node->GetMesh();
	uint32_t controlPointCount = currentMesh->GetControlPointsCount();
	for (int i = 0; i < controlPointCount; i++)
	{
		ControlPoint* currentControlPoint = new ControlPoint;
		Vec3 currentPosition;
		currentPosition.x = static_cast<float>(currentMesh->GetControlPointAt(i).mData[0]);
		currentPosition.y = static_cast<float>(currentMesh->GetControlPointAt(i).mData[1]);
		currentPosition.z = static_cast<float>(currentMesh->GetControlPointAt(i).mData[2]);
		currentControlPoint->Position = currentPosition;
		m_ControlPoints[i] = currentControlPoint;
	}
}

void SkeletonAnimation::SkeletonJointsAndAnimations(FbxNode * node)
{
	FbxMesh* currentMesh = node->GetMesh();

	uint32_t numDeformer = currentMesh->GetDeformerCount();

	FbxAMatrix identityMatrix = GeometryTransformation(node);

	for (int deformerIndex = 0; deformerIndex < numDeformer; deformerIndex++)
	{
		FbxSkin* currentSkin = reinterpret_cast<FbxSkin*>(currentMesh->GetDeformer(deformerIndex, FbxDeformer::eSkin));

		if (!currentSkin)
		{
			std::cout << "NO SKIN!" << std::endl;
		}

		uint32_t numCluster = currentSkin->GetClusterCount();
		for (int clusterIndex = 0; clusterIndex < numCluster; clusterIndex++)
		{

			FbxCluster* currentCluster = currentSkin->GetCluster(clusterIndex);

			// This is where we access the joint with GetLink().
			std::string currentJointName = currentCluster->GetLink()->GetName();
			uint32_t currentJointIndex = FindJointIndex(currentJointName);


			// Matrices
			FbxAMatrix transformMat;
			FbxAMatrix transformLinkMat;
			FbxAMatrix globalBindposeInverseMat;


			//first.g
			currentCluster->GetTransformMatrix(transformMat);
			currentCluster->GetTransformLinkMatrix(transformLinkMat);
			globalBindposeInverseMat = transformLinkMat.Inverse() * transformMat * identityMatrix;

			//Convert to mat4
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					float first = globalBindposeInverseMat[i][j];
					m_globalBindPoseMat[i][j] = first;
				}
			}
			glm::inverse(m_globalBindPoseMat);


			// Update skeleton
			m_Skeleton.Joints[currentJointIndex].GlobalBindposeInverse = globalBindposeInverseMat;
			m_Skeleton.Joints[currentJointIndex].Node = currentCluster->GetLink();

			int * clusterInd = currentCluster->GetControlPointIndices();
			uint32_t vertCount = currentCluster->GetControlPointIndicesCount();

			for (int vertIndex = 0; vertIndex < vertCount; vertIndex++)
			{
				int boneVertexIndex = clusterInd[vertIndex];
				int currentJoint = currentJointIndex;
				float boneWeight = (float)currentCluster->GetControlPointWeights()[vertIndex];

				BlendingIndexWeightPair pair;
				pair.VertIndex = boneVertexIndex;
				pair.BlendingIndex = currentJoint;
				pair.BlendingWeight = boneWeight;
				m_skinWeights.push_back(pair);
			}


			FbxAnimStack* currentAnimStack = m_Scene->GetSrcObject<FbxAnimStack>(0);
			FbxString currentAnimStackName = currentAnimStack->GetName();
			std::string mAnimName = currentAnimStackName.Buffer();
			FbxTakeInfo* takeInfo = m_Scene->GetTakeInfo(currentAnimStackName);

			FbxTime start = takeInfo->mLocalTimeSpan.GetStart();
			FbxTime end = takeInfo->mLocalTimeSpan.GetStop();

			FbxLongLong animationLength = end.GetFrameCount(FbxTime::eFrames24) - start.GetFrameCount(FbxTime::eFrames24) + 1;
			m_firstFrame = start.GetFrameCount(FbxTime::eFrames24);
			m_lastFrame = end.GetFrameCount(FbxTime::eFrames24);

		//	std::cout << m_firstFrame << std::endl;
			//std::cout << m_lastFrame << std::endl;
			Keyframe** currentKeyFrame = &m_Skeleton.Joints[currentJointIndex].Animation;



			for (FbxLongLong i = start.GetFrameCount(FbxTime::eFrames24); i <= end.GetFrameCount(FbxTime::eFrames24); i++)
			{
				FbxTime currentTime;
				currentTime.SetFrame(i, FbxTime::eFrames24);
				*currentKeyFrame = new Keyframe();
				(*currentKeyFrame)->FrameNum = i;
				FbxAMatrix currentTransformOffset = node->EvaluateLocalTransform(currentTime) * identityMatrix;
				(*currentKeyFrame)->LocalTransform = currentTransformOffset.Inverse() * currentCluster->GetLink()->EvaluateLocalTransform(currentTime);

				glm::vec3 tempTransform, tempRotation, tempScale;

				//Transformation information
				tempTransform.x = (*currentKeyFrame)->LocalTransform.GetT().mData[0];
				tempTransform.y = (*currentKeyFrame)->LocalTransform.GetT().mData[1];
				tempTransform.z = (*currentKeyFrame)->LocalTransform.GetT().mData[2];
				m_localTransformMat.push_back(tempTransform);

				//Rotation information
				tempRotation.x = (*currentKeyFrame)->LocalTransform.GetR().mData[0];
				tempRotation.y = (*currentKeyFrame)->LocalTransform.GetR().mData[1];
				tempRotation.z = (*currentKeyFrame)->LocalTransform.GetR().mData[2];
				m_localRotationMat.push_back(tempRotation);

				//Scaling information
				tempScale.x = (*currentKeyFrame)->LocalTransform.GetS().mData[0];
				tempScale.y = (*currentKeyFrame)->LocalTransform.GetS().mData[1];
				tempScale.z = (*currentKeyFrame)->LocalTransform.GetS().mData[2];
				m_localScaleMat.push_back(tempScale);
			
				std::cout << tempTransform.x << " " << tempTransform.y << " " << tempTransform.z << std::endl;
				currentKeyFrame = &((*currentKeyFrame)->Next);

			}
		}
	}
}



void SkeletonAnimation::CheckMesh(FbxNode * node)
{




	if (node->GetNodeAttribute())
	{
		switch (node->GetNodeAttribute()->GetAttributeType())
		{
			//std::cout << node->GetName() << std::endl;
		case FbxNodeAttribute::eMesh:
			FixControlPoints(node);
			if (m_HasAnimation)
			{
				SkeletonJointsAndAnimations(node);
			}
			
			break;
		}
	}

	for (int i = 0; i < node->GetChildCount(); i++)
	{

		CheckMesh(node->GetChild(i));

	}
}

void SkeletonAnimation::GetAnimation()
{

	for (int i = 0; i < m_Skeleton.Joints.size(); i++)
	{

		FbxVector4 translation = m_Skeleton.Joints[i].GlobalBindposeInverse.GetT();
		FbxVector4 rotation = m_Skeleton.Joints[i].GlobalBindposeInverse.GetR();
		translation.Set(translation.mData[0], translation.mData[1], translation.mData[2]);
		rotation.Set(rotation.mData[0], rotation.mData[1], rotation.mData[2]);
		m_Skeleton.Joints[i].GlobalBindposeInverse.SetT(translation);
		m_Skeleton.Joints[i].GlobalBindposeInverse.SetR(rotation);
		FbxMatrix finalMat = m_Skeleton.Joints[i].GlobalBindposeInverse;
		finalMat = finalMat.Transpose();

	}
}

std::vector<BlendingIndexWeightPair> SkeletonAnimation::GetWeights()const
{
	return m_skinWeights;
}

std::vector<int*> SkeletonAnimation::GetClusterInd()
{
	return m_clusterInd;
}

void SkeletonAnimation::Export()
{
	SkeletonHierachy(m_Scene->GetRootNode());
	if (m_Skeleton.Joints.empty())
	{
		m_HasAnimation = false;
	}

	CheckMesh(m_Scene->GetRootNode());

	if (m_HasAnimation)
	{
		GetAnimation();
	}
}

void SkeletonAnimation::SetScene(FbxScene * scene)
{
	m_Scene = scene;
}



int32_t SkeletonAnimation::GetFirstKeyFrame() {
	
	return m_firstFrame;
}

int32_t SkeletonAnimation::GetLastKeyFrame() {

	return m_lastFrame;
}


void SkeletonAnimation::SetBindPose(int32_t &bindPoseJointID, glm::mat4 &BindPoseMatrix) {

	bindPoseJointID = m_index.at(0);
	BindPoseMatrix = m_globalBindPoseMat;

}

std::vector<int32_t> SkeletonAnimation::GetJointID() {

	for (int i = 0; i < m_index.size(); i++) {
		std::cout << m_index.at(i) << std::endl;
	}
	return  m_index;
}

std::vector<int32_t> SkeletonAnimation::GetParentID() {

	return  m_parentIndex;
}

std::vector<glm::vec3>SkeletonAnimation::GetTransformationMatrices(){
	return m_localTransformMat;
}
std::vector<glm::vec3>SkeletonAnimation::GetRotationMatrices(){
	return m_localRotationMat;
}
std::vector<glm::vec3>SkeletonAnimation::GetScalingMatrices(){
	return m_localScaleMat;
}