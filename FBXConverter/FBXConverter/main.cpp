#include "Manager.h"
#include <iostream>
#pragma comment(lib, "libfbxsdk.lib")


int main(int argc, char** argv) {
	std::vector<glm::vec3> t;

	Manager m_mananger;

	m_mananger.Init();

	m_mananger.Run();



	getchar();
	return 0;
}