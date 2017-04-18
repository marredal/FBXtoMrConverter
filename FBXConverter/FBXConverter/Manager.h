#ifndef __MANAGER_H__
#define __MANAGER_H__

#include "fbxsdk.h"
#include <vector>
#include <iostream>
#include "VertexInfo.h"
#include "glm.hpp"
#include <iostream>

class Manager
{
public:
	Manager();
	virtual ~Manager();
	void Init();
	void Run();

private:
	FbxManager*		m_Manager;
	FbxScene*		m_Scene;
	FbxImporter*	m_Importer;

	FbxNode*		m_root;
	
	
	VertexInfo		m_vertexInfo;
};



#endif // !__MANAGER_H__
