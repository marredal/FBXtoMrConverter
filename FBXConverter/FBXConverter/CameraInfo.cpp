#include "CameraInfo.h"



CameraInfo::CameraInfo()
{
}


CameraInfo::~CameraInfo()
{
}

void CameraInfo::FillNodeArrayWithCamerasRecursive(FbxNode * node)
{

	if (node)
	{
		if (node->GetNodeAttribute())
		{
			if (node->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eCamera)
			{
				m_nodeArray.Add(node);
			}
		}

		for (int i = 0; i < node->GetChildCount(); i++)
		{
			FillNodeArrayWithCamerasRecursive(node->GetChild(i));
		}
	}
}

void CameraInfo::FillNodeArrayWithCameras(FbxScene * scene)
{
	m_nodeArray.Clear();

	FillNodeArrayWithCamerasRecursive(scene->GetRootNode());
}

void CameraInfo::FillCameraArray(FbxScene* scene)
{
	FillNodeArrayWithCameras(scene);

	for (int i = 0; i < m_nodeArray.Size(); i++)
	{
		FbxCamera* fbxCameraTemp = m_nodeArray[i]->GetCamera();

		Camera cameraTemp(fbxCameraTemp);

		m_cameraArray.push_back(cameraTemp);
	}
}

std::vector<Camera> CameraInfo::getCameraArray()
{
	return m_cameraArray;
}
