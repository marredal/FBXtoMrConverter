#ifndef __MANAGER_H__
#define __MANAGER_H__

#include "fbxsdk.h"
#include <vector>
#include <iostream>
#include "VertexInfo.h"
#include "SkeletonAnimation.h"
#include "glm.hpp"
#include <iostream>
#include "MaterialHandler.h"


class Manager
{
public:
	Manager();
	virtual ~Manager();
	void Init(const char* filepath);
	void Run(VertexInfo &target);
	void Run(SkeletonAnimation &target);


	//..::GET FUNCTIONS::..//
	//std::vector<glm::vec3> GetPos();



private:
	FbxManager*		m_Manager;
	FbxScene*		m_Scene;
	FbxImporter*	m_Importer;
	FbxNode*		m_root;

	MaterialHandler m_materialInfo;
	
	//VertexInfo		m_vertexInfo;
};



#endif // !__MANAGER_H__
