#include "Manager.h"
#include "SuperExporter.h"
#include <iostream>
#pragma comment(lib, "libfbxsdk.lib")


int main(int argc, char** argv) {


	MeshInfo temp;
	Manager m_mananger;

	m_mananger.Init();

	m_mananger.Run();

	m_mananger.GetMesh(temp);

	SuperExporter se;
	se.Run();

	return 0;
}