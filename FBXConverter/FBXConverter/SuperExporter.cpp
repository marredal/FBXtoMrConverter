#include "SuperExporter.h"

#include <MrHandler.h>
#include "VertexInfo.h"

SuperExporter::SuperExporter()
{

}


SuperExporter::~SuperExporter()
{
}

void SuperExporter::Run()
{
	bool isRunning = true;

	while (isRunning)
	{
		int input = 0;

		system("CLS");

		std::cout << "HELLO AND WELCOME TO THE FBX TO MR CONVERT." << std::endl;
		std::cout << "My name is mr Edwar Scully and I am here to assist you." << std::endl;
		std::cout << std::endl << std::endl;

		std::cout << "What would you like to do?" << std::endl;
		std::cout << "(1) CONVERT" << std::endl;
		std::cout << "(0) EXIT" << std::endl;
		std::cout << "INPUT :: ";
		std::cin >> input;
		switch (input)
		{
		case 1:
			Convert();
			break;
		case 0:
			isRunning = false;
		default:
			break;
		}
	}
}

void SuperExporter::Convert()
{
	int input = 0;

	system("CLS");

	std::cout << "I HOPE YOU HAVE BUT ALL THE FBX FILES IN THE FBX FOLDER" << std::endl;
	std::cout << std::endl << std::endl;

	std::cout << "What would you like to do?" << std::endl;
	std::cout << "(1) ADD MESH" << std::endl;
	std::cout << "(2) ADD SKELETON" << std::endl;
	std::cout << "(3) ADD ANIMATION" << std::endl;
	std::cout << "(4) EXPORT" << std::endl;
	std::cout << "(0) EXIT" << std::endl;
	std::cout << "INPUT :: ";
	std::cin >> input;



}

void SuperExporter::AddMesh(VertexInfo &target)
{
	m_mesh = new mr::MrMeshHandler;
	//target = new VertexInfo;

	glm::vec3 hej[1] = { glm::vec3(0.0f) };
	glm::vec4 hejj[1] = { glm::vec4(0.0f) };

	uint32_t t = 8;
	m_mesh->SetNumVerts(1);
	m_mesh->SetPositions(&target.GetPos()[0]);
	m_mesh->SetNormals(&target.GetNormal()[0]);
	m_mesh->SetTexCoords(&target.GetUV()[0]);
	m_mesh->SetBiTangents(&hej[0]);
	m_mesh->SetTangents(&hej[0]);
	m_mesh->SetSkinWeights(&hejj[0]);
	m_mesh->SetJointIDs(&hejj[0]);

	m_mesh->Export("hej.mr");
}

void SuperExporter::AddSkeleton()
{

}

void SuperExporter::AddAnimation()
{
	
}

void SuperExporter::Export()
{

}
