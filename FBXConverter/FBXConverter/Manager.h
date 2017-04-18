#ifndef __MANAGER_H__
#define __MANAGER_H__

#include "fbxsdk.h"
#include <vector>
#include <iostream>
#include "VertexInfo.h"

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

private:
	FbxManager*		m_Manager;
	FbxScene*		m_Scene;
	FbxImporter*	m_Importer;

	FbxNode* m_root;


	VertexInfo();

};



#endif // !__MANAGER_H__
