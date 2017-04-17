#include "Exporter.h"



Exporter::Exporter()
{
	// Do nothing...
}


Exporter::~Exporter()
{
	// Do nothing...
}

void Exporter::Init()
{
	m_Manager = FbxManager::Create();
	FbxIOSettings* ioSettings = FbxIOSettings::Create(m_Manager, IOSROOT);
	m_Manager->SetIOSettings(ioSettings);
	m_Importer = FbxImporter::Create(m_Manager, "");
	bool importInit = m_Importer->Initialize(".\\Assets\\hej5.fbx", -1, m_Manager->GetIOSettings());
	if (!importInit)
	{
		std::cout << "Error importing file!" << std::endl;
		getchar();
		return;
	}

	m_Scene = FbxScene::Create(m_Manager, "FBX Scene");
	m_Importer->Import(m_Scene);
	m_Importer->Destroy();
}

void Exporter::Shutdown()
{
	m_Manager->Destroy();
}

FbxAMatrix Exporter::GeometryTransformation(FbxNode * node)
{
	FbxVector4 translation = node->GetGeometricTranslation(FbxNode::eSourcePivot);
	FbxVector4 rotation = node->GetGeometricRotation(FbxNode::eSourcePivot);
	FbxVector4 scaling = node->GetGeometricScaling(FbxNode::eSourcePivot);

	return FbxAMatrix(translation, rotation, scaling);
}

void Exporter::SkeletonHierachyRecursive(FbxNode * node, int index, int parentIndex)
{
	if (node->GetNodeAttribute() && node->GetNodeAttribute() && node->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eSkeleton)
	{
		std::cout << "SKELETON: " << node->GetName() << std::endl;
		Joint currentJoint;
		currentJoint.ParentIndex = parentIndex;
		currentJoint.Name = node->GetName();
		m_Skeleton.Joints.push_back(currentJoint);
	}

	for (int i = 0; i < node->GetChildCount(); i++)
	{
		SkeletonHierachyRecursive(node->GetChild(i), m_Skeleton.Joints.size(), index);
	}
}

void Exporter::SkeletonHierachy(FbxNode * node)
{
	for (int i = 0; i < node->GetChildCount(); i++)
	{
		FbxNode* currentNode = node->GetChild(i);
		SkeletonHierachyRecursive(currentNode, 0, -1);
	}
}

uint32_t Exporter::FindJointIndex(const std::string & name)
{
	for (int i = 0; i < m_Skeleton.Joints.size(); i++)
	{
		if (m_Skeleton.Joints[i].Name == name)
		{
			return i;
		}
	}
}

void Exporter::fixControlPoints(FbxNode * node)
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

void Exporter::SkeletonJointsAndAnimations(FbxNode * node)
{
	std::cout << "SkeletonJointsAndAnimations" << std::endl;
	FbxMesh* currentMesh = node->GetMesh();

	uint32_t numDeformer = currentMesh->GetDeformerCount();

	FbxAMatrix identityMatrix = GeometryTransformation(node);

	for (int i = 0; i < numDeformer; i++)
	{
		FbxSkin* currentSkin = reinterpret_cast<FbxSkin*>(currentMesh->GetDeformer(i, FbxDeformer::eSkin));

		if (!currentSkin)
		{
			std::cout << "NO SKIN!" << std::endl;
		}
		else
		{
			uint32_t numClusters = currentSkin->GetClusterCount();
			for (int j = 0; j < numClusters; j++)
			{
				FbxCluster* currentCluster = currentSkin->GetCluster(j);

				// This is where we access the real joint, via GetLink().
				std::string currentJointName = currentCluster->GetLink()->GetName();
				uint32_t currentJointIndex = FindJointIndex(currentJointName);

				// Matrices
				FbxAMatrix transformMat;
				FbxAMatrix transformLinkMat;
				FbxAMatrix globalBindposeInverseMat;

				currentCluster->GetTransformMatrix(transformMat);
				currentCluster->GetTransformLinkMatrix(transformLinkMat);
				globalBindposeInverseMat = transformLinkMat.Inverse() * transformMat * identityMatrix;

				// Update skeleton
				m_Skeleton.Joints[currentJointIndex].GlobalBindposeInverse = globalBindposeInverseMat;
				m_Skeleton.Joints[currentJointIndex].Node = currentCluster->GetLink();

				uint32_t numIndices = currentCluster->GetControlPointIndicesCount();
				for (int g = 0; g < numIndices; g++)
				{
					BlendingIndexWeightPair currentBlendingIndexWeightPair;
					currentBlendingIndexWeightPair.BlendingIndex = currentJointIndex;
					currentBlendingIndexWeightPair.BlendingWeight = currentCluster->GetControlPointWeights()[i];
					m_ControlPoints[currentCluster->GetControlPointIndices()[i]]->BlendingInfo.push_back(currentBlendingIndexWeightPair);
				}

				FbxAnimStack* currentAnimStack = m_Scene->GetSrcObject<FbxAnimStack>(0);
				FbxString currentAnimStackName = currentAnimStack->GetName();
				std::string mAnimName = currentAnimStackName.Buffer();
				FbxTakeInfo* takeInfo = m_Scene->GetTakeInfo(currentAnimStackName);
				FbxTime start = takeInfo->mLocalTimeSpan.GetStart();
				FbxTime end = takeInfo->mLocalTimeSpan.GetStop();
				FbxLongLong mAnimationLength = end.GetFrameCount(FbxTime::eFrames24) - start.GetFrameCount(FbxTime::eFrames24) + 1;
				Keyframe** currentAnimation = &m_Skeleton.Joints[currentJointIndex].Animation;

				for (FbxLongLong i = start.GetFrameCount(FbxTime::eFrames24); i <= end.GetFrameCount(FbxTime::eFrames24); i++)
				{
					FbxTime currentTime;
					currentTime.SetFrame(i, FbxTime::eFrames24);
					*currentAnimation = new Keyframe();
					(*currentAnimation)->FrameNum = i;
					FbxAMatrix currentTransformOffset = node->EvaluateGlobalTransform(currentTime) * identityMatrix;
					(*currentAnimation)->GlobalTransform = currentTransformOffset.Inverse() * currentCluster->GetLink()->EvaluateGlobalTransform(currentTime);
					currentAnimation = &((*currentAnimation)->Next);
				}

			}

		}

	}
}

void Exporter::checkMesh(FbxNode * node)
{
	if (node->GetNodeAttribute())
	{
		switch (node->GetNodeAttribute()->GetAttributeType())
		{
		case FbxNodeAttribute::eMesh:
			fixControlPoints(node);
			SkeletonJointsAndAnimations(node);
			break;
		}
	}

	for (int i = 0; i < node->GetChildCount(); i++)
	{
		checkMesh(node->GetChild(i));
	}
}
