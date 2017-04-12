#include <fbxsdk.h>
#pragma comment(lib, "libfbxsdk.lib")

#include <iostream>

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
		return "Don't know";
	}
}

void PrintNodeAttribute(FbxNodeAttribute* nodeAttribute)
{
	FbxString nodeTypeName = GetNodeAttributeTypeName(nodeAttribute->GetAttributeType());
	FbxString nodeAttributeName = nodeAttribute->GetName();

	std::cout << "nodeTypeName: " << nodeTypeName.Buffer() << std::endl;
	std::cout << "nodeAttributeName: " << nodeAttributeName.Buffer() << std::endl;

	return;
}

void PrintNode(FbxNode* node)
{
	const char* nodeName = node->GetName();

	FbxDouble3 nodeTranslation = node->LclTranslation.Get();
	FbxDouble3 nodeRotation = node->LclRotation.Get();
	FbxDouble3 nodeScaling = node->LclScaling.Get();

	std::cout << "Node name: " << nodeName << std::endl;
	std::cout << "Translation: (" << nodeTranslation[0] << ", " << nodeTranslation[1] << ", " << nodeTranslation[2]  << ")" << std::endl;
	std::cout << "Rotation: (" << nodeRotation[0] << ", " << nodeRotation[1] << ", " << nodeRotation[2] << ")" << std::endl;
	std::cout << "Scaling: (" << nodeScaling[0] << ", " << nodeScaling[1] << ", " << nodeScaling[2] << ")" << std::endl;


	// Print attributes
	for (int i = 0; i < node->GetNodeAttributeCount(); i++)
	{
		PrintNodeAttribute(node->GetNodeAttributeByIndex(i));
	}

	// Print children
	for (int i = 0; i < node->GetChildCount(); i++)
	{
		PrintNode(node->GetChild(i));
	}

	std::cout << "<node>" << std::endl;

}

int main(int argc, char** argv)
{

	FbxManager* manager = FbxManager::Create();

	FbxIOSettings* ioSettings = FbxIOSettings::Create(manager, IOSROOT);
	ioSettings->SetBoolProp(IMP_FBX_MATERIAL, true);
	ioSettings->SetBoolProp(IMP_FBX_TEXTURE, false);
	ioSettings->SetBoolProp(IMP_FBX_ANIMATION, false);

	manager->SetIOSettings(ioSettings);

	FbxImporter* importer = FbxImporter::Create(manager, "");
	bool importInit = importer->Initialize(".\\Assets\\hej2.fbx", -1, manager->GetIOSettings());
	if (!importInit)
	{
		std::cout << "Error importing file!" << std::endl;
		getchar();
		return 1;
	}

	FbxScene* scene = FbxScene::Create(manager, "FBX Scene");
	importer->Import(scene);

	//Importer is done
	importer->Destroy();

	FbxNode* rootNode = scene->GetRootNode();

	for (int i = 0; i < rootNode->GetChildCount(); i++)
	{
		PrintNode(rootNode->GetChild(i));
	}


	getchar();
	// Destroy at bottom
	manager->Destroy();


	return 0;
}