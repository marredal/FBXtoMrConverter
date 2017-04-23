#ifndef __SUPEREXPORTER_H__
#define __SUPEREXPORTER_H__

#include "Manager.h"
#include "MrHandler.h"
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
	void Export();

private:
	//VertexInfo * m_target;
	//Manager m_manager;

	MrSkelHandler * m_skel;
	MrAnimHandler * m_animHandler;
	MrMeshHandler * m_mesh;
	
};


#endif	// ! __SUPEREXPORTER_H__