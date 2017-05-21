#ifndef __SUPEREXPORTER_H__
#define __SUPEREXPORTER_H__

#include "Manager.h"
#include "MrHandler.h"
#include "MrMatHandler.h"
#include "SkeletonAnimation.h"
#include "glm\gtx\transform.hpp"

#include <vector>
#include <iostream>
#include "Manager.h"

class SuperExporter
{
public:
	SuperExporter();
	virtual ~SuperExporter();

	void Run();
	void Convert();
	void AddMesh();
	void AddSkeleton();
	void AddAnimation();
	void AddMaterial();
	void Export();
	void CalculateTangents(VertexInfo & vertInfo, std::vector<glm::vec3> & tangents, std::vector<glm::vec3> & biTangents);

private:
	//VertexInfo * m_target;
	//Manager m_manager;

	MrSkelHandler * m_skel;
	MrAnimHandler * m_animHandler;
	MrMeshHandler * m_mesh;
	MrMatHandler  * m_mat;
	
};


#endif	// ! __SUPEREXPORTER_H__