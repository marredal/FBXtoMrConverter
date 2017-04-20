#ifndef __SUPEREXPORTER_H__
#define __SUPEREXPORTER_H__


#include "MrHandler.h"


#include <iostream>
#include "Manager.h"


class SuperExporter
{
public:
	SuperExporter();
	virtual ~SuperExporter();

	void Run();
	void Convert();
	void AddMesh(VertexInfo &target);
	void AddSkeleton();
	void AddAnimation();
	void Export();

private:
	//VertexInfo * m_target;


	mr::MrAnimHandler * m_animHandler;
	mr::MrMeshHandler * m_mesh;
	
};


#endif	// ! __SUPEREXPORTER_H__