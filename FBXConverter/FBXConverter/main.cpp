#define FBXSDK_SHARED
#include "SkeletonAnimation.h"

//void Init()
//{
//	manager = FbxManager::Create();
//
//	FbxIOSettings* ioSettings = FbxIOSettings::Create(manager, IOSROOT);
//	//ioSettings->SetBoolProp(IMP_FBX_MATERIAL, true);
//	//ioSettings->SetBoolProp(IMP_FBX_TEXTURE, true);
//	//ioSettings->SetBoolProp(IMP_FBX_ANIMATION, false);
//
//	manager->SetIOSettings(ioSettings);
//
//	importer = FbxImporter::Create(manager, "");
//	bool importInit = importer->Initialize(".\\Assets\\hej5.fbx", -1, manager->GetIOSettings());
//	if (!importInit)
//	{
//		std::cout << "Error importing file!" << std::endl;
//		getchar();
//		return;
//	}
//
//	scene = FbxScene::Create(manager, "FBX Scene");
//	importer->Import(scene);
//	importer->Destroy();
//}

// Function
//FbxString GetNodeAttributeTypeName(FbxNodeAttribute::EType nodeType)
//{
//	switch (nodeType)
//	{
//	case FbxNodeAttribute::eUnknown:
//		return "unidentified";
//	case FbxNodeAttribute::eNull:
//		return "null";
//	case FbxNodeAttribute::eMarker:
//		return "marker";
//	case FbxNodeAttribute::eSkeleton:
//		return "skeleton";
//	case FbxNodeAttribute::eMesh:
//		return "mesh";
//	case FbxNodeAttribute::eNurbs:
//		return "nurbs";
//	case FbxNodeAttribute::ePatch:
//		return "patch";
//	case FbxNodeAttribute::eCamera:
//		return "camera";
//	case FbxNodeAttribute::eCameraStereo:
//		return "stereo";
//	case FbxNodeAttribute::eCameraSwitcher:
//		return "camera switcher";
//	case FbxNodeAttribute::eLight:
//		return "light";
//	case FbxNodeAttribute::eOpticalReference:
//		return "optical reference";
//	case FbxNodeAttribute::eOpticalMarker:
//		return "marker";
//	case FbxNodeAttribute::eNurbsCurve:
//		return "nurbs curve";
//	case FbxNodeAttribute::eTrimNurbsSurface:
//		return "trim nurbs surface";
//	case FbxNodeAttribute::eBoundary:
//		return "boundary";
//	case FbxNodeAttribute::eNurbsSurface:
//		return "nurbs surface";
//	case FbxNodeAttribute::eShape:
//		return "shape";
//	case FbxNodeAttribute::eLODGroup:
//		return "lodgroup";
//	case FbxNodeAttribute::eSubDiv:
//		return "subdiv";
//	default:
//		return "Don't know type";
//	}
//}
//
//void PrintNodeAttribute(FbxNodeAttribute* nodeAttribute)
//{
//	FbxString nodeTypeName = GetNodeAttributeTypeName(nodeAttribute->GetAttributeType());
//	FbxString nodeAttributeName = nodeAttribute->GetName();
//
//	std::cout << "nodeTypeName: " << nodeTypeName.Buffer() << std::endl;
//	std::cout << "nodeAttributeName: " << nodeAttributeName.Buffer() << std::endl << std::endl;
//
//	return;
//}
//
//void PrintNode(FbxNode* node)
//{
//	const char* nodeName = node->GetName();
//
//	FbxDouble3 nodeTranslation = node->LclTranslation.Get();
//	FbxDouble3 nodeRotation = node->LclRotation.Get();
//	FbxDouble3 nodeScaling = node->LclScaling.Get();
//
//	std::cout << "Node name: " << nodeName << std::endl;
//	std::cout << "Translation: (" << nodeTranslation[0] << ", " << nodeTranslation[1] << ", " << nodeTranslation[2] << ")" << std::endl;
//	std::cout << "Rotation: (" << nodeRotation[0] << ", " << nodeRotation[1] << ", " << nodeRotation[2] << ")" << std::endl;
//	std::cout << "Scaling: (" << nodeScaling[0] << ", " << nodeScaling[1] << ", " << nodeScaling[2] << ")" << std::endl;
//
//	FbxNodeAttribute::EType nodeType;
//	nodeType = node->GetNodeAttribute()->GetAttributeType();
//	int counter = 0;
//	// Print attributes
//	for (int i = 0; i < node->GetNodeAttributeCount(); i++)
//	{
//		if (GetNodeAttributeTypeName(node->GetNodeAttributeByIndex(i)->GetAttributeType()) == "skeleton")
//		{
//			std::cout << "Tjena" << counter << std::endl;
//			counter++;
//			//PrintNodeAttribute(node->GetNodeAttributeByIndex(i));
//		}
//	}
//
//	// Print material
//	//for (int i = 0; i < node->GetMaterialCount(); i++)
//	//{
//	//	FbxSurfaceMaterial* material = node->GetMaterial(i);
//	//	std::cout << "Material: " << material->GetName() << std::endl;
//	//}
//
//
//	// Recursive
//	for (int i = 0; i < node->GetChildCount(); i++)
//	{
//		PrintNode(node->GetChild(i));
//	}
//
//}


// Structs

//struct Keyframe
//{
//	FbxLongLong mFrameNum;
//	FbxAMatrix mGlobalTransform;
//	Keyframe* mNext;
//
//	Keyframe() :
//		mNext(nullptr)
//	{}
//};
//
//struct Joint
//{
//	std::string mName;
//	int mParentIndex;
//	FbxAMatrix mGlobalBindposeInverse;
//	Keyframe* mAnimation;
//	FbxNode* mNode;
//
//	Joint() :
//		mNode(nullptr),
//		mAnimation(nullptr)
//	{
//		mGlobalBindposeInverse.SetIdentity();
//		mParentIndex = -1;
//	}
//
//	~Joint()
//	{
//		while (mAnimation)
//		{
//			Keyframe* temp = mAnimation->mNext;
//			delete mAnimation;
//			mAnimation = temp;
//		}
//	}
//};
//
//struct Skeleton
//{
//	std::vector<Joint> mJoints;
//};
//
//struct BlendingIndexWeightPair
//{
//	uint32_t mBlendingIndex;
//	double mBlendingWeight;
//
//	BlendingIndexWeightPair() :
//		mBlendingIndex(0),
//		mBlendingWeight(0)
//	{}
//};
//
//struct Vec3
//{
//	float x;
//	float y;
//	float z;
//};
//
//struct CtrlPoint
//{
//	Vec3 mPosition;
//	std::vector<BlendingIndexWeightPair> mBlendingInfo;
//
//	CtrlPoint()
//	{
//		mBlendingInfo.reserve(4);
//	}
//};


// Skeleton
//Skeleton mSkeleton;
//
//std::unordered_map<uint32_t, CtrlPoint*>mControlPoints;
//
//FbxAMatrix GeometryTransformation(FbxNode* node)
//{
//	FbxVector4 translation = node->GetGeometricTranslation(FbxNode::eSourcePivot);
//	FbxVector4 rotation = node->GetGeometricRotation(FbxNode::eSourcePivot);
//	FbxVector4 scaling = node->GetGeometricScaling(FbxNode::eSourcePivot);
//
//	return FbxAMatrix(translation, rotation, scaling);
//}

//void SkeletonHierachyRecursive(FbxNode* node, int index, int parentIndex)
//{
//	if (node->GetNodeAttribute() && node->GetNodeAttribute() && node->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eSkeleton)
//	{
//		std::cout << "SKELETON: " << node->GetName() << std::endl;
//		Joint currentJoint;
//		currentJoint.mParentIndex = parentIndex;
//		currentJoint.mName = node->GetName();
//		mSkeleton.mJoints.push_back(currentJoint);
//	}
//
//	for (int i = 0; i < node->GetChildCount(); i++)
//	{
//		SkeletonHierachyRecursive(node->GetChild(i), mSkeleton.mJoints.size(), index);
//	}
//}

//void SkeletonHierachy(FbxNode* node)
//{
//	for (int i = 0; i < node->GetChildCount(); i++)
//	{
//		FbxNode* currentNode = node->GetChild(i);
//		SkeletonHierachyRecursive(currentNode, 0, -1);
//	}
//}

//uint32_t FindJointIndex(const std::string& name)
//{
//	for (int i = 0; i < mSkeleton.mJoints.size(); i++)
//	{
//		if (mSkeleton.mJoints[i].mName == name)
//		{
//			return i;
//		}
//	}
//}

//void fixControlPoints(FbxNode* node)
//{
//	FbxMesh* currentMesh = node->GetMesh();
//	uint32_t controlPointCount = currentMesh->GetControlPointsCount();
//	for (int i = 0; i < controlPointCount; i++)
//	{
//		CtrlPoint* currentControlPoint = new CtrlPoint;
//		Vec3 currentPosition;
//		currentPosition.x = static_cast<float>(currentMesh->GetControlPointAt(i).mData[0]);
//		currentPosition.y = static_cast<float>(currentMesh->GetControlPointAt(i).mData[1]);
//		currentPosition.z = static_cast<float>(currentMesh->GetControlPointAt(i).mData[2]);
//		currentControlPoint->mPosition = currentPosition;
//		mControlPoints[i] = currentControlPoint;
//	}
//}

//void SkeletonJointsAndAnimations(FbxNode* node)
//{
//	std::cout << "SkeletonJointsAndAnimations" << std::endl;
//	FbxMesh* currentMesh = node->GetMesh();
//
//	uint32_t numDeformer = currentMesh->GetDeformerCount();
//
//	FbxAMatrix identityMatrix = GeometryTransformation(node);
//
//	for (int i = 0; i < numDeformer; i++)
//	{
//		FbxSkin* currentSkin = reinterpret_cast<FbxSkin*>(currentMesh->GetDeformer(i, FbxDeformer::eSkin));
//
//		if (!currentSkin)
//		{
//			std::cout << "NO SKIN!" << std::endl;
//		}
//		else
//		{
//			uint32_t numClusters = currentSkin->GetClusterCount();
//			for (int j = 0; j < numClusters; j++)
//			{
//				FbxCluster* currentCluster = currentSkin->GetCluster(j);
//
//				// This is where we access the real joint, via GetLink().
//				std::string currentJointName = currentCluster->GetLink()->GetName();
//				uint32_t currentJointIndex = FindJointIndex(currentJointName);
//
//				// Matrices
//				FbxAMatrix transformMat;
//				FbxAMatrix transformLinkMat;
//				FbxAMatrix globalBindposeInverseMat;
//
//				currentCluster->GetTransformMatrix(transformMat);
//				currentCluster->GetTransformLinkMatrix(transformLinkMat);
//				globalBindposeInverseMat = transformLinkMat.Inverse() * transformMat * identityMatrix;
//
//				// Update skeleton
//				mSkeleton.mJoints[currentJointIndex].mGlobalBindposeInverse = globalBindposeInverseMat;
//				mSkeleton.mJoints[currentJointIndex].mNode = currentCluster->GetLink(); 
//
//				uint32_t numIndices = currentCluster->GetControlPointIndicesCount();
//				for (int g = 0; g < numIndices; g++)
//				{
//					BlendingIndexWeightPair currentBlendingIndexWeightPair;
//					currentBlendingIndexWeightPair.mBlendingIndex = currentJointIndex;
//					currentBlendingIndexWeightPair.mBlendingWeight = currentCluster->GetControlPointWeights()[i];
//					mControlPoints[currentCluster->GetControlPointIndices()[i]]->mBlendingInfo.push_back(currentBlendingIndexWeightPair);
//				}
//
//				FbxAnimStack* currentAnimStack = scene->GetSrcObject<FbxAnimStack>(0);
//				FbxString currentAnimStackName = currentAnimStack->GetName();
//				std::string mAnimName = currentAnimStackName.Buffer();
//				FbxTakeInfo* takeInfo = scene->GetTakeInfo(currentAnimStackName);
//				FbxTime start = takeInfo->mLocalTimeSpan.GetStart();
//				FbxTime end = takeInfo->mLocalTimeSpan.GetStop();
//				FbxLongLong mAnimationLength = end.GetFrameCount(FbxTime::eFrames24) - start.GetFrameCount(FbxTime::eFrames24) + 1;
//				Keyframe** currentAnimation = &mSkeleton.mJoints[currentJointIndex].mAnimation;
//
//				for (FbxLongLong i = start.GetFrameCount(FbxTime::eFrames24); i <= end.GetFrameCount(FbxTime::eFrames24); i++)
//				{
//					FbxTime currentTime;
//					currentTime.SetFrame(i, FbxTime::eFrames24);
//					*currentAnimation = new Keyframe();
//					(*currentAnimation)->mFrameNum = i;
//					FbxAMatrix currentTransformOffset = node->EvaluateGlobalTransform(currentTime) * identityMatrix;
//					(*currentAnimation)->mGlobalTransform = currentTransformOffset.Inverse() * currentCluster->GetLink()->EvaluateGlobalTransform(currentTime);
//					currentAnimation = &((*currentAnimation)->mNext);
//				}
//
//			}
//
//		}
//
//	}
//
//}
//
//void checkMesh(FbxNode* node)
//{
//	if (node->GetNodeAttribute())
//	{
//		switch (node->GetNodeAttribute()->GetAttributeType())
//		{
//		case FbxNodeAttribute::eMesh:
//			fixControlPoints(node);
//			SkeletonJointsAndAnimations(node);
//			break;
//		}
//	}
//
//	for (int i = 0; i < node->GetChildCount(); i++)
//	{
//		checkMesh(node->GetChild(i));
//	}
//}



int main(int argc, char** argv)
{
	Exporter* exporter = new Exporter();
	exporter->Init();
	exporter->GetSkeleton();

	getchar();
	exporter->Shutdown();
	return 0;
}