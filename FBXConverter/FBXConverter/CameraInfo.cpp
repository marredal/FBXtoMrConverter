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
			FbxCamera* camera = node->GetCamera();
			if (camera != NULL)
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

void CameraInfo::FillNodeArrayWithCameras(FbxNode * node)
{
	m_nodeArray.Clear();

	FillNodeArrayWithCamerasRecursive(node);
}

void CameraInfo::FillCameraArray(FbxNode* node)
{
	FillNodeArrayWithCameras(node);

	for (int i = 0; i < m_nodeArray.Size(); i++)
	{
		FbxCamera* fbxCameraTemp = m_nodeArray[i]->GetCamera();

		Camera cameraTemp(fbxCameraTemp);

		m_cameraArray.push_back(cameraTemp);

		PrintCamera0Info();
	}
}

std::vector<Camera> CameraInfo::getCameraArray()
{
	return m_cameraArray;
}

void CameraInfo::PrintCamera0Info()
{
	std::cout << "Aspect Ratio: " << m_cameraArray[0].GetAspectRatio().x << m_cameraArray[0].GetAspectRatio().y << std::endl;

	std::cout << "Far Plane: " << m_cameraArray[0].GetFarPlane() << std::endl;

	std::cout << "FOV: " << m_cameraArray[0].GetFOV() << std::endl;

	std::cout << "Look At x: " << m_cameraArray[0].GetLookAt().x << std::endl;

	std::cout << "Near Plane: " << m_cameraArray[0].GetNearPlane() << std::endl;
}
