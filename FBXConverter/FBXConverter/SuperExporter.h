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
	void AddMesh();
	void AddSkeleton();
	void AddAnimation();
	void Export();

private:
	MR::MrAnimHandler * m_animHandler;
	
};


#endif	// ! __SUPEREXPORTER_H__