#include "Manager.h"
#include "VertexInfo.h"
#include "SuperExporter.h"
#include <iostream>
#pragma comment(lib, "libfbxsdk.lib")


int main(int argc, char** argv) {
	std::vector<glm::vec3> t;
	VertexInfo target;


	Manager m_mananger;

	m_mananger.Init();

	m_mananger.Run(target);

	SuperExporter hej;
	hej.AddMesh(target);
	
	



	SuperExporter se;
	se.Run();

	return 0;
}