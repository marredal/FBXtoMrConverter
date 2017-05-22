#ifndef __SUPEREXPORTER_H__
#define __SUPEREXPORTER_H__

#include "Manager.h"
#include "MrHandler.h"
#include "MrMatHandler.h"
#include "MrLightHandler.h"
#include "SkeletonAnimation.h"
#include "MrCameraHandler.h"
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
	bool Convert();
	void AddMesh();
	void AddSkeleton();
	void AddAnimation();
	void AddMaterial();
	void AddCamera();
	void AddLight();
	void Material();
	void CalculateTangents(VertexInfo & vertInfo, std::vector<glm::vec3> & tangents, std::vector<glm::vec3> & biTangents);
	
};


#endif	// ! __SUPEREXPORTER_H__