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

//		system("CLS");

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

//	system("CLS");

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

	uint32_t numVerts = target.GetPos().size();
	

	glm::vec3 * pos =		new glm::vec3[numVerts];
	glm::vec3 * nor =		new glm::vec3[numVerts];
	glm::vec2 * uv =		new glm::vec2[numVerts];
	glm::vec3 * tan =		new glm::vec3[numVerts];
	glm::vec3 * bi =		new glm::vec3[numVerts];
	glm::vec4 * id =		new glm::vec4[numVerts];
	glm::vec4 * we =		new glm::vec4[numVerts];




	for (uint32_t i = 0; i < numVerts; i++)
	{
		pos[i] = glm::vec3(target.GetPos()[i].x, target.GetPos()[i].y, target.GetPos()[i].z);
		nor[i] =  glm::vec3(target.GetNormal()[i].x, target.GetNormal()[i].y, target.GetNormal()[i].z);
		uv[i] = glm::vec2(target.GetUV()[i].x, target.GetUV()[i].y);
		tan[i] = glm::vec3(1.0f);
		bi[i] = glm::vec3(1.0f);
		id[i] = glm::vec4(1.0f);
		we[i] = glm::vec4(1.0f);
	}

	m_mesh->SetNumVerts(numVerts);
	m_mesh->SetPositions(&pos[0]);
	m_mesh->SetNormals(&nor[0]);
	m_mesh->SetTexCoords(&uv[0]);
	m_mesh->SetTangents(&tan[0]);
	m_mesh->SetBiTangents(&bi[0]);
	m_mesh->SetSkinWeights(&id[0]);
	m_mesh->SetJointIDs(&we[0]);

	m_mesh->Export("New.mr");


	getchar();
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
