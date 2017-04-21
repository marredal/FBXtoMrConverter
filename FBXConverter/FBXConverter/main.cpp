#include "Manager.h"
#include "SuperExporter.h"
#include <iostream>
#pragma comment(lib, "libfbxsdk.lib")


int main(int argc, char** argv) {
	std::vector<glm::vec3> t;
	VertexInfo target;
	SkeletonAnimation skeleludvigefag;
	Manager m_mananger;

	m_mananger.Init();

	m_mananger.Run(target);
	m_mananger.Run(skeleludvigefag);
	skeleludvigefag.GetName();
	SuperExporter hej;
	hej.AddMesh(target);
	
	



	SuperExporter se;
	se.Run();

	return 0;
}