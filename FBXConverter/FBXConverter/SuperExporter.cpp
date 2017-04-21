#include "SuperExporter.h"

#include <MrHandler.h>
#include "VertexInfo.h"

SuperExporter::SuperExporter()
{
	m_skel = new mr::MrSkelHandler;
	m_mesh = new mr::MrMeshHandler;
	m_animHandler = new mr::MrAnimHandler;
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
		std::cin.ignore();
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

	bool isRunning = true;

	while (isRunning)
	{

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
		std::cin.ignore();

		switch (input)
		{
		case 1:
			break;
		case 2:
			AddSkeleton();
			break;
		case 3:
			AddAnimation();
			break;
		case 4:
		{
			Export();

			break;
		}
		case 0:
			isRunning = false;
			break;
		default:
			break;
		}

	}

}

void SuperExporter::AddMesh(VertexInfo &target)
{
	std::cout << "Input scene to import: " << std::endl;
	std::cout << "INPUT :: ";





	m_mesh = new mr::MrMeshHandler;
	//target = new VertexInfo


	&target.GetNormal();

	glm::vec3 * pos = new glm::vec3[8];
	glm::vec3 * nor = new glm::vec3[8];
	glm::vec2 * uv = new glm::vec2[8];
	glm::vec3 * tan = new glm::vec3[8];
	glm::vec3 * bi = new glm::vec3[8];
	glm::vec4 * id = new glm::vec4[8];
	glm::vec4 * we = new glm::vec4[8];;


	uint32_t numVerts = target.GetPos().size();


	for (uint32_t i = 0; i < 8; i++)
	{
		pos[i] = glm::vec3(target.GetPos()[i].x, target.GetPos()[i].y, target.GetPos()[i].z);
		nor[i] =  glm::vec3(target.GetNormal()[i].x, target.GetNormal()[i].y, target.GetNormal()[i].z);
		uv[i] = glm::vec2(target.GetUV()[i].x, target.GetUV()[i].y);
		tan[i] = glm::vec3(1.0f);
		bi[i] = glm::vec3(1.0f);
		id[i] = glm::vec4(1.0f);
		we[i] = glm::vec4(1.0f);
	}

	m_mesh->SetNumVerts(8);
	m_mesh->SetPositions(&pos[0]);
	m_mesh->SetNormals(&nor[0]);
	m_mesh->SetTexCoords(&uv[0]);
	m_mesh->SetTangents(&tan[0]);
	m_mesh->SetBiTangents(&bi[0]);
	m_mesh->SetSkinWeights(&id[0]);
	m_mesh->SetJointIDs(&we[0]);

	m_mesh->Export("hej.mr");

	mr::MrMeshHandler in;
	in.Import("hej.mr");

	std::cout << "hej.mr" << in.GetPositions()[0].x << std::endl;

	getchar();

	// CLEAR SCENE
}

void SuperExporter::AddSkeleton()
{
	Manager manager;

	bool isRunning = true;
	
	while (isRunning)
	{

		std::string name;
		std::string path;

		std::string fullpath = ".\\FBX\\";

		std::cout << "Scene with skeleton: " << std::endl;
		std::cout << "INPUT :: .\\FBX\\";
		std::getline(std::cin, path);
		fullpath.append(path);

		std::cout << "Name the animation: " << std::endl;
		std::cout << "INPUT ::";
		std::getline(std::cin, name);


		int input = 0;

		std::cout << "What would you like to do?" << std::endl;
		std::cout << "(1) DONE" << std::endl;
		std::cout << "(2) REDO" << std::endl;
		std::cout << "(0) BACK" << std::endl;
		std::cout << "INPUT :: ";

		std::cin >> input;
		std::cin.ignore();

		switch (input)
		{
		case 1: 
		{
			manager.Init(fullpath.c_str());
			VertexInfo info;
			SkeletonAnimation skel;
			manager.Run(info);
			manager.Run(skel);

			//std::vector<uint32_t> ids = static_cast<std::vector<uint32_t>>(skel.GetJointID());
			int size = skel.GetParentID().size();
			glm::mat4 * localMat = new glm::mat4[size];
			uint32_t * ids = new uint32_t[size];
			uint32_t * parIDs = new uint32_t[size];

			for (int i = 0; i < size; i++)
			{
				glm::mat4 posMat = glm::translate(skel.GetTransformationMatrices()[i]);

				glm::mat4 xRot = glm::rotate(skel.GetRotationMatrices()[i].x, glm::vec3(1.0, 0.0, 0.0));
				glm::mat4 yRot = glm::rotate(skel.GetRotationMatrices()[i].y, glm::vec3(0.0, 1.0, 0.0));
				glm::mat4 zRot = glm::rotate(skel.GetRotationMatrices()[i].z, glm::vec3(0.0, 0.0, 1.0));

				glm::mat4 rotMat = zRot * yRot * xRot;

				glm::mat4 scaleMat = glm::scale(skel.GetScalingMatrices()[i]);

				glm::mat4 mat = posMat * rotMat * scaleMat;

				localMat[i] = mat;
				ids[i] = skel.GetJointID()[0];
				parIDs[i] = skel.GetParentID()[0];
			}
			
			// I GUESS THIS IS IT // MJ
			m_skel->SetIDs(ids);
			m_skel->SetParentIDs(parIDs);
			m_skel->SetMatrix(localMat);
			m_skel->SetNumJoints(size);


			isRunning = false;

			system("CLS");

			std::cout << "OMG YOU ARE GOOD AT THIS :D // ES" << std::endl;
			break;
		}
		case 2:
			break;
		case 0:
			isRunning = false;
			break;
		default:
			break;
		}

	}
}

void SuperExporter::AddAnimation()
{

//	m_manager.Init(".\\Assets\\kranen.fbx");
	SkeletonAnimation skel;
//	skel.SetBindPose(joint, matrix);


	Manager manager;

	bool isRunning = true;

	while (isRunning)
	{

		std::string name;
		std::string path;

		std::string fullpath = ".\\FBX\\";

		std::cout << "Scene with skeleton: " << std::endl;
		std::cout << "INPUT :: .\\FBX\\";
		std::getline(std::cin, path);
		fullpath.append(path);

		std::cout << "Name the animation: " << std::endl;
		std::cout << "INPUT ::";
		std::getline(std::cin, name);


		int input = 0;

		std::cout << "What would you like to do?" << std::endl;
		std::cout << "(1) DONE" << std::endl;
		std::cout << "(2) REDO" << std::endl;
		std::cout << "(0) BACK" << std::endl;
		std::cout << "INPUT :: ";

		std::cin >> input;
		std::cin.ignore();

		switch (input)
		{
		case 1:
		{
			manager.Init(fullpath.c_str());
			VertexInfo info;
			SkeletonAnimation skel;
			manager.Run(info);
			manager.Run(skel);
			mr::MrAnimHandler * animHandler = new mr::MrAnimHandler;
			
			int numJoints = skel.GetParentID().size();
			int numKeys = skel.GetTransformationMatrices().size() / skel.GetParentID().size();

			mr::MrKeyFramedJoint * key = new mr::MrKeyFramedJoint[numKeys];
			
			for (int i = 0; i < numKeys; i++)
			{
				glm::mat4 * localMat = new glm::mat4[numJoints];
				
				int32_t * ids = new int32_t[numJoints];
			//	int32_t * parIDs = new int32_t[numJoints];

				for (int i = 0; i < numJoints; i++)
				{
					glm::mat4 posMat = glm::translate(skel.GetTransformationMatrices()[i]);

					glm::mat4 xRot = glm::rotate(skel.GetRotationMatrices()[i].x, glm::vec3(1.0, 0.0, 0.0));
					glm::mat4 yRot = glm::rotate(skel.GetRotationMatrices()[i].y, glm::vec3(0.0, 1.0, 0.0));
					glm::mat4 zRot = glm::rotate(skel.GetRotationMatrices()[i].z, glm::vec3(0.0, 0.0, 1.0));

					glm::mat4 rotMat = zRot * yRot * xRot;

					glm::mat4 scaleMat = glm::scale(skel.GetScalingMatrices()[i]);

					glm::mat4 mat = posMat * rotMat * scaleMat;

					ids[i] = 0;
					localMat[i] = mat;

				}

				key[i].keyFrames = ids;
				key[i].jointID = 0;
				key[i].numKeyframes = numJoints;
				key[i].matrix = localMat;


			}

			m_animHandler->SetName("HEJ");
			
			m_animHandler->SetKeyframedJoint(key);
			m_animHandler->SetNumKeyFramedJoints(numKeys);
			m_animHandler->SetFirstKeyFrame(1);
			m_animHandler->SetLastKeyFrame(numKeys);

			isRunning = false;

			break;
		}
		case 2:
			break;
		default:
			break;
		
		}
	}
}

void SuperExporter::Export()
{
	mr::MrHandler * handler = new mr::MrHandler;

	handler->SetName("HEJ");
	handler->SetMeshHandlers(nullptr, 0);
	handler->SetSkelHandlers(m_skel, 1);
	handler->SetAnimHandlers(m_animHandler, 1);


	handler->Export();
}
