#ifndef __SUPEREXPORTER_H__
#define __SUPEREXPORTER_H__

#include "Manager.h"
#include "MrHandler.h"
#include "MrMatHandler.h"
#include "MrCameraHandler.h"
#include "MrLightHandler.h"
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
	bool Convert();
	void AddMesh();
	void AddSkeleton();
	void AddAnimation();
	void AddMaterial();
	void AddCamera();
	void AddLight();
	void AddTexture(MrTexture * textures, std::string fullpath, int index, uint32_t type);
	
};


#endif	// ! __SUPEREXPORTER_H__