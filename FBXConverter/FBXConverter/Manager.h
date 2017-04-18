#ifndef __MANAGER_H__
#define __MANAGER_H__

#include "fbxsdk.h"
#include <vector>
#include <iostream>
#include "VertexInfo.h"
#include "glm.hpp"
#include <iostream>


struct MeshInfo
{
	std::vector<glm::vec3> pos;
	std::vector<glm::vec3> nor;
	std::vector<glm::vec2> uv;

}; 

struct Vec3 {
	float x;
	float y;
	float z;
};

class Manager
{
public:
	Manager();
	virtual ~Manager();
	void Init();
	void Run();
	MeshInfo GetMesh(MeshInfo info);


private:
	FbxManager*		m_Manager;
	FbxScene*		m_Scene;
	FbxImporter*	m_Importer;

	FbxNode*		m_root;
	
	
	VertexInfo		m_vertexInfo;

};



#endif // !__MANAGER_H__
