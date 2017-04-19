#include "Manager.h"
#include "SuperExporter.h"
#include <iostream>
#pragma comment(lib, "libfbxsdk.lib")


int main(int argc, char** argv) {
	std::vector<glm::vec3> t;

	Manager m_mananger;

	m_mananger.Init();

	m_mananger.Run();

	SuperExporter hej;
	hej.AddMesh();
	



	getchar();
	return 0;
}