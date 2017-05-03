#ifndef __CAMERAINFO_H__
#define __CAMERAINFO_H__

#include "Camera.h"
#include <vector>


class CameraInfo
{
public:
	CameraInfo();
	virtual ~CameraInfo();

	void FillCameraArray(FbxScene* scene);

	std::vector<Camera> getCameraArray();


private:
	void FillNodeArrayWithCamerasRecursive(FbxNode* node);
	void FillNodeArrayWithCameras(FbxScene* scene);

	std::vector<Camera> m_cameraArray;
	FbxArray<FbxNode*>	m_nodeArray;


};

#endif // !__CAMERAINFO_H__