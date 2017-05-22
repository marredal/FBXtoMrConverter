#ifndef __CAMERAINFO_H__
#define __CAMERAINFO_H__

#define FBXSDK_SHARED

#include "Camera.h"
#include <vector>
#include <iostream>


class CameraInfo
{
public:
	CameraInfo();
	virtual ~CameraInfo();

	void FillCameraArray(FbxNode* scene);

	std::vector<Camera> getCameraArray();

	void PrintCamera0Info(int value);


private:
	void FillNodeArrayWithCamerasRecursive(FbxNode* node);
	void FillNodeArrayWithCameras(FbxNode* scene);

	std::vector<Camera> m_cameraArray;
	FbxArray<FbxNode*>	m_nodeArray;


};

#endif // !__CAMERAINFO_H__