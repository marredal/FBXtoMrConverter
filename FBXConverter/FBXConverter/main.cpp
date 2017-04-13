#include <fbxsdk.h>
#pragma comment(lib, "libfbxsdk.lib")


#include <iostream>
#include <vector>



// Function
FbxString GetNodeAttributeTypeName(FbxNodeAttribute::EType nodeType)
{
	switch (nodeType)
	{
	case FbxNodeAttribute::eUnknown:
		return "unidentified";
	case FbxNodeAttribute::eNull:
		return "null";
	case FbxNodeAttribute::eMarker:
		return "marker";
	case FbxNodeAttribute::eSkeleton:
		return "skeleton";
	case FbxNodeAttribute::eMesh:
		return "mesh";
	case FbxNodeAttribute::eNurbs:
		return "nurbs";
	case FbxNodeAttribute::ePatch:
		return "patch";
	case FbxNodeAttribute::eCamera:
		return "camera";
	case FbxNodeAttribute::eCameraStereo:
		return "stereo";
	case FbxNodeAttribute::eCameraSwitcher:
		return "camera switcher";
	case FbxNodeAttribute::eLight:
		return "light";
	case FbxNodeAttribute::eOpticalReference:
		return "optical reference";
	case FbxNodeAttribute::eOpticalMarker:
		return "marker";
	case FbxNodeAttribute::eNurbsCurve:
		return "nurbs curve";
	case FbxNodeAttribute::eTrimNurbsSurface:
		return "trim nurbs surface";
	case FbxNodeAttribute::eBoundary:
		return "boundary";
	case FbxNodeAttribute::eNurbsSurface:
		return "nurbs surface";
	case FbxNodeAttribute::eShape:
		return "shape";
	case FbxNodeAttribute::eLODGroup:
		return "lodgroup";
	case FbxNodeAttribute::eSubDiv:
		return "subdiv";
	default:
		return "Don't know type";
	}
}

void PrintNodeAttribute(FbxNodeAttribute* nodeAttribute)
{
	FbxString nodeTypeName = GetNodeAttributeTypeName(nodeAttribute->GetAttributeType());
	FbxString nodeAttributeName = nodeAttribute->GetName();

	std::cout << "nodeTypeName: " << nodeTypeName.Buffer() << std::endl;
	std::cout << "nodeAttributeName: " << nodeAttributeName.Buffer() << std::endl << std::endl;

	return;
}

void PrintNode(FbxNode* node)
{
	const char* nodeName = node->GetName();

	FbxDouble3 nodeTranslation = node->LclTranslation.Get();
	FbxDouble3 nodeRotation = node->LclRotation.Get();
	FbxDouble3 nodeScaling = node->LclScaling.Get();

	std::cout << "Node name: " << nodeName << std::endl;
	std::cout << "Translation: (" << nodeTranslation[0] << ", " << nodeTranslation[1] << ", " << nodeTranslation[2] << ")" << std::endl;
	std::cout << "Rotation: (" << nodeRotation[0] << ", " << nodeRotation[1] << ", " << nodeRotation[2] << ")" << std::endl;
	std::cout << "Scaling: (" << nodeScaling[0] << ", " << nodeScaling[1] << ", " << nodeScaling[2] << ")" << std::endl;

	FbxNodeAttribute::EType nodeType;
	nodeType = node->GetNodeAttribute()->GetAttributeType();
	int counter = 0;
	// Print attributes
	for (int i = 0; i < node->GetNodeAttributeCount(); i++)
	{
		if (GetNodeAttributeTypeName(node->GetNodeAttributeByIndex(i)->GetAttributeType()) == "skeleton")
		{
			std::cout << "Tjena" << counter << std::endl;
			counter++;
			//PrintNodeAttribute(node->GetNodeAttributeByIndex(i));
		}
	}

	// Print material
	//for (int i = 0; i < node->GetMaterialCount(); i++)
	//{
	//	FbxSurfaceMaterial* material = node->GetMaterial(i);
	//	std::cout << "Material: " << material->GetName() << std::endl;
	//}


	// Recursive
	for (int i = 0; i < node->GetChildCount(); i++)
	{
		PrintNode(node->GetChild(i));
	}

}


// Structs

struct Keyframe
{
	FbxLongLong mFrameNum;
	FbxAMatrix mGlobalTransform;
	Keyframe* mNext;

	Keyframe() :
		mNext(nullptr)
	{}
};

struct Joint
{
	std::string mName;
	int mParentIndex;
	FbxAMatrix mGlobalBindposeInverse;
	Keyframe* mAnimation;
	FbxNode* mNode;

	Joint() :
		mNode(nullptr),
		mAnimation(nullptr)
	{
		mGlobalBindposeInverse.SetIdentity();
		mParentIndex = -1;
	}

	~Joint()
	{
		while (mAnimation)
		{
			Keyframe* temp = mAnimation->mNext;
			delete mAnimation;
			mAnimation = temp;
		}
	}
};

struct Skeleton
{
	std::vector<Joint> mJoints;
};

struct BlendingIndexWeightPair
{
	uint32_t mBlendingIndex;
	double mBlendingWeight;

	BlendingIndexWeightPair() :
		mBlendingIndex(0),
		mBlendingWeight(0)
	{}
};


// Skeleton
Skeleton mSkeleton;

FbxAMatrix GeometryTransformation(FbxNode* node)
{
	FbxVector4 translation = node->GetGeometricTranslation(FbxNode::eSourcePivot);
	FbxVector4 rotation = node->GetGeometricRotation(FbxNode::eSourcePivot);
	FbxVector4 scaling = node->GetGeometricScaling(FbxNode::eSourcePivot);

	return FbxAMatrix(translation, rotation, scaling);
}

void SkeletonHierachyRecursive(FbxNode* node, int index, int parentIndex)
{
	if (node->GetNodeAttribute() && node->GetNodeAttribute() && node->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eSkeleton)
	{
		std::cout << "SKELETON: " << node->GetName() << std::endl;
		Joint currentJoint;
		currentJoint.mParentIndex = parentIndex;
		currentJoint.mName = node->GetName();
		mSkeleton.mJoints.push_back(currentJoint);
	}

	for (int i = 0; i < node->GetChildCount(); i++)
	{
		SkeletonHierachyRecursive(node->GetChild(i), mSkeleton.mJoints.size(), index);
	}
}

void SkeletonHierachy(FbxNode* node)
{
	for (int i = 0; i < node->GetChildCount(); i++)
	{
		FbxNode* currentNode = node->GetChild(i);
		SkeletonHierachyRecursive(currentNode, 0, -1);
	}
}

uint32_t FindJointIndex(const std::string& name)
{
	for (int i = 0; i < mSkeleton.mJoints.size(); i++)
	{
		if (mSkeleton.mJoints[i].mName == name)
		{
			return i;
		}
	}
}

void SkeletonJointsAndAnimations(FbxNode* node)
{
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

				// This is where we access the REAL joint, via GetLink().
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
				mSkeleton.mJoints[currentJointIndex].mGlobalBindposeInverse = globalBindposeInverseMat;
				mSkeleton.mJoints[currentJointIndex].mNode = currentCluster->GetLink();

				uint32_t numIndices = currentCluster->GetControlPointIndicesCount();
				for (int g = 0; g < numIndices; g++)
				{
					BlendingIndexWeightPair currentBlendingIndexWeightPair;
					currentBlendingIndexWeightPair.mBlendingIndex = currentJointIndex;
					currentBlendingIndexWeightPair.mBlendingWeight = currentCluster->GetControlPointWeights()[i];
					
					//TODO Add mControlPoints, check FBXExporter.h from gamedev
				}

			}

		}

	}

}

int main(int argc, char** argv)
{
	FbxManager* manager = FbxManager::Create();

	FbxIOSettings* ioSettings = FbxIOSettings::Create(manager, IOSROOT);
	//ioSettings->SetBoolProp(IMP_FBX_MATERIAL, true);
	//ioSettings->SetBoolProp(IMP_FBX_TEXTURE, true);
	//ioSettings->SetBoolProp(IMP_FBX_ANIMATION, false);

	manager->SetIOSettings(ioSettings);

	FbxImporter* importer = FbxImporter::Create(manager, "");
	bool importInit = importer->Initialize(".\\Assets\\hej5.fbx", -1, manager->GetIOSettings());
	if (!importInit)
	{
		std::cout << "Error importing file!" << std::endl;
		getchar();
		return 1;
	}

	FbxScene* scene = FbxScene::Create(manager, "FBX Scene");
	importer->Import(scene);

	//Importer is done
	//importer->Destroy();
	FbxNode* rootNode = scene->GetRootNode();

	SkeletonHierachy(rootNode);

	getchar();
	// Destroy at bottom
	manager->Destroy();

	return 0;
}





