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
	}
}

std::vector<Camera> CameraInfo::getCameraArray()
{
	return m_cameraArray;
}

void CameraInfo::PrintCamera0Info(int value)
{
	std::cout << "Aspect Ratio x: " << m_cameraArray[value].GetAspectRatio().x << std::endl;
	std::cout << "Aspect Ratio y: " << m_cameraArray[value].GetAspectRatio().y << std::endl;

	std::cout << "Far Plane: " << m_cameraArray[value].GetFarPlane() << std::endl;

	std::cout << "FOV: " << m_cameraArray[value].GetFOV() << std::endl;

	std::cout << "Look At x: " << m_cameraArray[value].GetLookAt().x << std::endl;

	std::cout << "Near Plane: " << m_cameraArray[value].GetNearPlane() << std::endl;

	std::cout << "Position x: " << m_cameraArray[value].GetPosition().x << std::endl;
	std::cout << "Position y: " << m_cameraArray[value].GetPosition().y << std::endl;
	std::cout << "Position z: " << m_cameraArray[value].GetPosition().z << std::endl;
	std::cout << "----------------------------------------------" << std::endl;
}
