#include "SkeletonAnimation.h"



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
	bool importInit = m_Importer->Initialize(".\\Assets\\tjena5.fbx", -1, m_Manager->GetIOSettings());
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
	m_Scene->Destroy();
	m_Manager->Destroy();

	m_Skeleton.Joints.clear();
}

void Exporter::GetSkeleton()
{
	SkeletonHierachy(m_Scene->GetRootNode());

	// Maybe necessary we will see
	//if (m_Skeleton.Joints.empty())
	//{
	//	m_Animation = false;
	//}
	checkMesh(m_Scene->GetRootNode());
	GetAnimation();

}

FbxAMatrix Exporter::GeometryTransformation(FbxNode * node)
{
	const FbxVector4 translation = node->GetGeometricTranslation(FbxNode::eSourcePivot);
	const FbxVector4 rotation = node->GetGeometricRotation(FbxNode::eSourcePivot);
	const FbxVector4 scaling = node->GetGeometricScaling(FbxNode::eSourcePivot);

	return FbxAMatrix(translation, rotation, scaling);
}

void Exporter::SkeletonHierachyRecursive(FbxNode * node, int index, int parentIndex)
{
	if (node->GetNodeAttribute() && node->GetNodeAttribute() && node->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eSkeleton)
	{
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
		else
		{
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

				currentCluster->GetTransformMatrix(transformMat);
				currentCluster->GetTransformLinkMatrix(transformLinkMat);
				globalBindposeInverseMat = transformLinkMat.Inverse() * transformMat * identityMatrix;

				// Update skeleton
				m_Skeleton.Joints[currentJointIndex].GlobalBindposeInverse = globalBindposeInverseMat;
				m_Skeleton.Joints[currentJointIndex].Node = currentCluster->GetLink();

				uint32_t numIndice = currentCluster->GetControlPointIndicesCount();
				for (int indiceIndex = 0; indiceIndex < numIndice; indiceIndex++)
				{
					BlendingIndexWeightPair currentBlendingIndexWeightPair;
					currentBlendingIndexWeightPair.BlendingIndex = currentJointIndex;
					currentBlendingIndexWeightPair.BlendingWeight = currentCluster->GetControlPointWeights()[indiceIndex];
					m_ControlPoints[currentCluster->GetControlPointIndices()[indiceIndex]]->BlendingInfo.push_back(currentBlendingIndexWeightPair);
				}

				FbxAnimStack* currentAnimStack = m_Scene->GetSrcObject<FbxAnimStack>(0);
				FbxString currentAnimStackName = currentAnimStack->GetName();
				std::string mAnimName = currentAnimStackName.Buffer();
				FbxTakeInfo* takeInfo = m_Scene->GetTakeInfo(currentAnimStackName);
				FbxTime start = takeInfo->mLocalTimeSpan.GetStart();
				FbxTime end = takeInfo->mLocalTimeSpan.GetStop();
				FbxLongLong animationLength = end.GetFrameCount(FbxTime::eFrames24) - start.GetFrameCount(FbxTime::eFrames24) + 1;
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

		/*BlendingIndexWeightPair currBlendingIndexWeightPair;
		currBlendingIndexWeightPair.BlendingIndex = 0;
		currBlendingIndexWeightPair.BlendingWeight = 0;
		for (auto itr = m_ControlPoints.begin(); itr != m_ControlPoints.end(); ++itr)
		{
			for (unsigned int i = itr->second->BlendingInfo.size(); i <= 4; ++i)
			{
				itr->second->BlendingInfo.push_back(currBlendingIndexWeightPair);
			}
		}*/
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

void Exporter::GetAnimation()
{
	//for (int i = 0; i < m_Skeleton.Joints.size(); i++)
	//{
	//	FbxVector4 translation = m_Skeleton.Joints[i].GlobalBindposeInverse.GetT();
	//	FbxVector4 rotation = m_Skeleton.Joints[i].GlobalBindposeInverse.GetR();
	//	translation.Set(translation.mData[0], translation.mData[1], translation.mData[2]);
	//	rotation.Set(rotation.mData[0], rotation.mData[1], rotation.mData[2]);
	//	m_Skeleton.Joints[i].GlobalBindposeInverse.SetT(translation);
	//	m_Skeleton.Joints[i].GlobalBindposeInverse.SetR(rotation);
	//	FbxMatrix finalMat = m_Skeleton.Joints[i].GlobalBindposeInverse;
	//	finalMat = finalMat.Transpose();
	//}

	for (int i = 0; i < m_Skeleton.Joints.size(); i++)
	{
		std::cout << m_Skeleton.Joints[i].Name.c_str() << std::endl;

		Keyframe* swag = m_Skeleton.Joints[i].Animation;
		while (swag)
		{
			FbxVector4 translation = swag->GlobalTransform.GetT();
			FbxVector4 rotation = swag->GlobalTransform.GetR();
			translation.Set(translation.mData[0], translation.mData[1], translation.mData[2]);
			rotation.Set(rotation.mData[0], rotation.mData[1], rotation.mData[2]);
			swag->GlobalTransform.SetT(translation);
			swag->GlobalTransform.SetR(rotation);
			FbxMatrix yolo = swag->GlobalTransform;
			
			std::cout << swag->GlobalTransform.GetROnly().mData[0] << ", ";
			std::cout << swag->GlobalTransform.GetROnly().mData[1] << ", ";
			std::cout << swag->GlobalTransform.GetROnly().mData[2] << std::endl;

			swag = swag->Next;
		}
	}
}
