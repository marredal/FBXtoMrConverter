#include "Manager.h"
#include "SuperExporter.h"
#include "SkeletonAnimation.h"
#include <iostream>
#pragma comment(lib, "libfbxsdk.lib")


int main(int argc, char** argv) {
//	std::vector<glm::vec3> t;
//	VertexInfo target;
//	SkeletonAnimation skel;
//	Manager m_mananger;
//
//	m_mananger.Init();
//
//	m_mananger.Run(target);
//	m_mananger.Run(skel);
//
	SuperExporter super;
//	hej.AddMesh(target);
//	
//	
//
//
//
//	SuperExporter se;
	super.Run();

	return 0;
}