#ifndef __MANAGER_H__
#define __MANAGER_H__

#define FBXSDK_SHARED

#include "fbxsdk.h"
#include <vector>
#include <iostream>
#include "VertexInfo.h"
#include "SkeletonAnimation.h"
#include "glm.hpp"
#include <iostream>
#include "MaterialHandler.h"
#include "CameraInfo.h"
#include "LightHandler.h"


class Manager
{
public:
	Manager();
	virtual ~Manager();
	void Init(const char* filepath);
	void Run(VertexInfo &target);
	void Run(SkeletonAnimation &target);
	void Run(CameraInfo &target);
	void Run(LightHandler &target);


	//..::GET FUNCTIONS::..//
	//std::vector<glm::vec3> GetPos();



private:
	FbxManager*		m_Manager;
	FbxScene*		m_Scene;
	FbxImporter*	m_Importer;
	FbxNode*		m_root;

	MaterialHandler m_materialInfo;

	CameraInfo		m_camerainfo;

	LightHandler	m_lightHandler;


	
	//VertexInfo		m_vertexInfo;
};



#endif // !__MANAGER_H__
