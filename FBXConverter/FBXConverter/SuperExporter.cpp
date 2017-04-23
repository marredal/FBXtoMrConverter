#include "SuperExporter.h"

#include <MrHandler.h>
#include "VertexInfo.h"
#include <string>

SuperExporter::SuperExporter()
{
	m_skel = new MrSkelHandler;
	m_mesh = new MrMeshHandler;
	m_animHandler = new MrAnimHandler;
}


SuperExporter::~SuperExporter()
{
}

void SuperExporter::Run()
{
	system("CLS");
	bool isRunning = true;

	while (isRunning)
	{
		system("CLS");
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
	system("CLS");
	int input = 0;
	//	system("CLS");

	bool isRunning = true;

	while (isRunning)
	{
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
		std::cin.ignore();

		switch (input)
		{
		case 1:
			AddMesh();
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

void SuperExporter::AddMesh()
{
	system("CLS");

	std::string fullpath = ".\\FBX\\";
	std::string path;

	std::cout << "Scene with skeleton: " << std::endl;
	std::cout << "INPUT :: .\\FBX\\";
	std::getline(std::cin, path);
	fullpath.append(path);

	std::cout << "Input scene to import: " << std::endl;
	std::cout << "INPUT :: ";
	VertexInfo target;
	Manager m_manager;

	m_manager.Init(fullpath.c_str());
	m_manager.Run(target);
	SkeletonAnimation skel;
	m_manager.Run(skel);
	skel.GetJointID();


	m_mesh = new MrMeshHandler;

	int indSize = target.GetIndices().size();
	uint32_t numVerts = indSize; //target.getCount();
	std::vector<int> ind = target.GetIndices();

	glm::vec3 * pos = new glm::vec3[numVerts];
	glm::vec3 * nor = new glm::vec3[numVerts];
	glm::vec2 * uv = new glm::vec2[numVerts];
	glm::vec3 * tan = new glm::vec3[numVerts];
	glm::vec3 * bi = new glm::vec3[numVerts];
	glm::vec4 * id = new glm::vec4[numVerts];
	glm::vec4 * we = new glm::vec4[numVerts];

	int temp = skel.GetJointID().size();



	for (uint32_t i = 0; i < numVerts; i++)
	{
		pos[i] = glm::vec3(target.GetPos()[ind[i]].x, target.GetPos()[ind[i]].y, target.GetPos()[ind[i]].z);
		nor[i] =  glm::vec3(target.GetNormal()[ind[i]].x, target.GetNormal()[ind[i]].y, target.GetNormal()[ind[i]].z);
		uv[i] = glm::vec2(target.GetUV()[ind[i]].x, target.GetUV()[ind[i]].y);
		//tan[i] = glm::vec3(target.GetTangent()[i].x, target.GetTangent()[i].y,target.GetTangent()[i].z);
		//bi[i] = glm::vec3(target.GetBiTangent()[i].x, target.GetBiTangent()[i].y, target.GetBiTangent()[i].z);
	}


//	uint32_t naa = 0;
//	for (uint32_t i = 0; i < numVerts; i++)
//	{
//		for (uint32_t j = 0; j < 4; j++)
//		{
//			id[i][j] = skel.GetWeights()[naa].BlendingIndex;
//			naa++;
//		}
//	//	std::cout << id[i].x << " y " << id[i].y << " z " << id[i].z << std::endl;
//	}




	int t = 0;

	int skinSize = skel.GetWeights().size() / 4;
	for (uint32_t i = 0; i < skinSize; i++)
	{
		we[t].x = skel.GetWeights()[i].BlendingWeight;
		t++;
	}
	t = 0;
	for (uint32_t i = skinSize; i < skinSize * 2; i++)
	{
		we[t].y = skel.GetWeights()[i].BlendingWeight;
		t++;
	}
	t = 0;
	for (uint32_t i = skinSize * 2; i < skinSize * 3; i++)
	{
		we[t].z = skel.GetWeights()[i].BlendingWeight;
		t++;
	}
	t = 0;
	for (uint32_t i = skinSize * 3; i < skinSize * 4; i++)
	{
		we[t].w = skel.GetWeights()[i].BlendingWeight;
		t++;
	}


	t = 0;
	for (uint32_t i = 0; i < skinSize; i++)
	{
		id[t].x = skel.GetWeights()[i].BlendingIndex;
		t++;
	}
	t = 0;
	for (uint32_t i = skinSize; i < skinSize * 2; i++)
	{
		id[t].y = skel.GetWeights()[i].BlendingIndex;
		t++;
	}
	t = 0;
	for (uint32_t i = skinSize * 2; i < skinSize * 3; i++)
	{
		id[t].z = skel.GetWeights()[i].BlendingIndex;
		t++;
	}
	t = 0;
	for (uint32_t i = skinSize * 3; i < skinSize * 4; i++)
	{
		id[t].w = skel.GetWeights()[i].BlendingIndex;
		t++;
	}

	glm::vec4 * id2 = new glm::vec4[numVerts];
	glm::vec4 * we2 = new glm::vec4[numVerts];

	for (int i = 0; i < numVerts; i++)
	{
		id2[i] = id[ind[i]];
		we2[i] = we[ind[i]];
	}


	m_mesh->SetNumVerts(numVerts);
	m_mesh->SetPositions(&pos[0]);
	m_mesh->SetNormals(&nor[0]);
	m_mesh->SetTexCoords(&uv[0]);
	m_mesh->SetTangents(&tan[0]);
	m_mesh->SetBiTangents(&bi[0]);
	m_mesh->SetSkinWeights(&id[0]);
	m_mesh->SetJointIDs(&we[0]);

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
				glm::vec3 p(1, 1, 1);

				glm::mat4 posMat = glm::translate(skel.GetTransformationMatrices()[i]);
				//glm::mat4 posMat = glm::translate(p);

				glm::mat4 xRot = glm::rotate(skel.GetRotationMatrices()[i].x, glm::vec3(1.0, 0.0, 0.0));
				glm::mat4 yRot = glm::rotate(skel.GetRotationMatrices()[i].y, glm::vec3(0.0, 1.0, 0.0));
				glm::mat4 zRot = glm::rotate(skel.GetRotationMatrices()[i].z, glm::vec3(0.0, 0.0, 1.0));

				glm::mat4 rotMat = zRot * yRot * xRot;

				glm::mat4 scaleMat = glm::scale(skel.GetScalingMatrices()[i]);

				glm::mat4 mat = posMat * rotMat * scaleMat;

				localMat[i] = mat;
				ids[i] = skel.GetJointID()[i];
				parIDs[i] = skel.GetParentID()[i];

				std::cout << std::endl;
				std::cout <<"ID " << ids[i] << std::endl;
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
	system("CLS");
//	m_manager.Init(".\\Assets\\kranen.fbx");
	SkeletonAnimation skel;
//	skel.SetBindPose(joint, matrix);
	system("CLS");

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
			MrAnimHandler * animHandler = new MrAnimHandler;
			
			int numJoints = skel.GetParentID().size();
			int numKeys = skel.GetTransformationMatrices().size() / skel.GetParentID().size();

			MrKeyFramedJoint * key = new MrKeyFramedJoint[numKeys];
			
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

			m_animHandler->SetName("animation");
			
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
	system("CLS");

	std::string name;

	std::cout << "Name the file: " << std::endl;
	std::cout << "INPUT ::";
	std::getline(std::cin, name);


	MrHandler * handler = new MrHandler;

	handler->SetName(name.c_str());
	handler->SetMeshHandlers(m_mesh, 1);
	handler->SetSkelHandlers(m_skel, 1);
	handler->SetAnimHandlers(m_animHandler, 1);


	handler->Export();
	
	
}
