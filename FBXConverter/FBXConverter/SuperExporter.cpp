#include "SuperExporter.h"

#include <MrHandler.h>
#include "VertexInfo.h"
#include <string>
#include <iomanip>

#define STB_IMAGE_IMPLEMENTATION
#include "stb-master\stb_image.h"


SuperExporter::SuperExporter()
{
}


SuperExporter::~SuperExporter()
{
}

void SuperExporter::Run()
{
	system("CLS");
	bool isRunning = true;

	while (Convert());

}

bool SuperExporter::Convert()
{
	int input = 0;

	bool isRunning = true;

	std::cout << "What would you like to do?" << std::endl;
	std::cout << "(1) EXPORT MESH" << std::endl;
	std::cout << "(2) EXPORT SKELETON" << std::endl;
	std::cout << "(3) EXPORT ANIMATION" << std::endl;
	std::cout << "(4) CONVERT TEXTURE" << std::endl;
	std::cout << "(5) EXPORT MATERIAL" << std::endl;
	std::cout << "(6) EXPORT CAMERA" << std::endl;
	std::cout << "(7) EXPORT LIGHT" << std::endl;
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
		AddMaterial();
		break;
	case 5:
	{
		Material();
		break;
	}
	case 6:
		AddCamera();
		break;
	case 7:
		AddLight();
		break;
	case 0:
		return false;
		break;
	default:
		break;
	}



	return true;
}

void SuperExporter::AddMesh()
{
	system("CLS");

	int hasSkinWeights = 0;

	std::string fullpath = ".\\FBX\\";
	std::string path;

	std::cout << "Scene with mesh: " << std::endl;
	std::cout << "INPUT :: .\\FBX\\";
	std::getline(std::cin, path);
	fullpath.append(path);

	std::cout << "Export skin weights: " << std::endl;
	std::cout << "(1) YES" << std::endl;
	std::cout << "(2) NO" << std::endl;
	std::cout << "INPUT :: ";
	std::cin >> hasSkinWeights;
	std::cin.ignore();


	VertexInfo target;
	Manager manager;

	SkeletonAnimation skel;
	MrMeshHandler * mesh = new MrMeshHandler;

	if (hasSkinWeights == 1)
	{
		manager.Run(skel);
		mesh->SetHasSkinWeights(true);
	}
	else
	{
		mesh->SetHasSkinWeights(false);
	}


	int32_t hasAttrib;
	std::cout << "Has custom attribute: " << std::endl;
	std::cout << "(1) YES" << std::endl;
	std::cout << "(2) NO" << std::endl;
	std::cout << "INPUT :: ";
	std::cin >> hasAttrib;
	std::cin.ignore();

	if (hasAttrib == 1)
	{
		manager.Run(skel);
		mesh->SetHasAttrib(true);
		mesh->SetAttrib(target.GetAttrib());
	}
	else
	{
		mesh->SetHasAttrib(false);
	}


	manager.Init(fullpath.c_str());
	manager.Run(target);

	CameraInfo camInfo;
	manager.Run(camInfo);
	skel.GetJointID();



	int indSize = target.GetIndices().size();
	uint32_t numVerts = indSize; //target.getCount();
	std::vector<int> ind = target.GetIndices();

	glm::vec3 * pos = new glm::vec3[numVerts];
	glm::vec3 * nor = new glm::vec3[numVerts];
	glm::vec2 * uv = new glm::vec2[numVerts];
	glm::vec3 * tan = new glm::vec3[numVerts];
	glm::vec3 * bi = new glm::vec3[numVerts];

	int temp = 0;
	glm::vec4 * id;
	glm::vec4 * we;
	glm::vec4 * id2;
	glm::vec4 * we2;

	if (hasSkinWeights == 1)
	{

		id = new glm::vec4[numVerts];
		we = new glm::vec4[numVerts];
		skel.GetJointID().size();
	}

	for (uint32_t i = 0; i < numVerts; i++)
	{
		pos[i] = glm::vec3(target.GetPos()[ind[i]].x, target.GetPos()[ind[i]].y, target.GetPos()[ind[i]].z);
		nor[i] = glm::vec3(target.GetNormal()[ind[i]].x, target.GetNormal()[ind[i]].y, target.GetNormal()[ind[i]].z);
		uv[i] = glm::vec2(target.GetUV()[i].x, target.GetUV()[i].y);
		//tan[i] = glm::vec3(target.GetTangent()[i].x, target.GetTangent()[i].y,target.GetTangent()[i].z);
		//bi[i] = glm::vec3(target.GetBiTangent()[i].x, target.GetBiTangent()[i].y, target.GetBiTangent()[i].z);
	}

	if (hasSkinWeights == 1)
	{
		for (uint32_t i = 0; i < target.getCount(); i++)
		{
			int t = 0;
			for (uint32_t j = 0; j < skel.GetWeights().size(); j++)
			{
				if (i == skel.GetWeights()[j].VertIndex)
				{
					if (t < 4)
					{
						id[i][t] = (float)skel.GetWeights()[j].BlendingIndex;
						we[i][t] = (float)skel.GetWeights()[j].BlendingWeight;
						t++;
					}
				}
			}
		}

		glm::vec4 * id2 = new glm::vec4[numVerts];
		glm::vec4 * we2 = new glm::vec4[numVerts];

		for (int i = 0; i < numVerts; i++)
		{
			id2[i] = id[ind[i]];
			we2[i] = we[ind[i]];

			float total = we2[i].x + we2[i].y + we2[i].z + we2[i].w;
			std::cout << total << std::endl;
		}
	}

	mesh->SetNumVerts(numVerts);
	mesh->SetPositions(&pos[0]);
	mesh->SetNormals(&nor[0]);
	mesh->SetTexCoords(&uv[0]);
	mesh->SetTangents(&tan[0]);
	mesh->SetBiTangents(&bi[0]);


	if (hasSkinWeights == 1)
	{
		mesh->SetSkinWeights(&we2[0]);
		mesh->SetJointIDs(&id2[0]);
	}

	fullpath = ".\\Assets\\Meshes\\";

	std::cout << "Name: " << std::endl;
	std::cout << "INPUT :: .\\Assets\\Meshes\\";
	std::getline(std::cin, path);
	fullpath.append(path);
	fullpath.append(".mrmesh");
	mesh->Export(fullpath.c_str());
}


void SuperExporter::AddSkeleton()
{
	Manager manager;
	MrSkelHandler * skelHandler = new MrSkelHandler;

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

			int offset = skel.GetRotationMatrices().size() / skel.GetJointID().size();

			for (int i = 0; i < size; i++)
			{
				glm::vec3 p(1, 1, 1);

				glm::mat4 posMat = glm::translate(skel.GetTransformationMatrices()[i * offset]);
				//glm::mat4 posMat = glm::translate(p);

				glm::mat4 xRot = glm::rotate(glm::radians(skel.GetRotationMatrices()[i * offset].x), glm::vec3(1.0, 0.0, 0.0));
				glm::mat4 yRot = glm::rotate(glm::radians(skel.GetRotationMatrices()[i * offset].y), glm::vec3(0.0, 1.0, 0.0));
				glm::mat4 zRot = glm::rotate(glm::radians(skel.GetRotationMatrices()[i * offset].z), glm::vec3(0.0, 0.0, 1.0));

				glm::mat4 rotMat = zRot * yRot * xRot;

				glm::mat4 scaleMat = glm::scale(skel.GetScalingMatrices()[i * offset]);

				glm::mat4 mat = posMat * rotMat * scaleMat;

				localMat[i] = mat;
				ids[i] = skel.GetJointID()[i];
				parIDs[i] = skel.GetParentID()[i];

				std::cout << std::endl;
				std::cout << "ID " << ids[i] << std::endl;
			}

			skelHandler->SetIDs(ids);
			skelHandler->SetParentIDs(parIDs);
			skelHandler->SetMatrix(localMat);
			skelHandler->SetNumJoints(size);




			std::string fullpath = ".\\Assets\\Skeletons\\";

			std::cout << "Name: " << std::endl;
			std::cout << "INPUT :: .\\Assets\\Skeletons\\";
			std::getline(std::cin, path);
			fullpath.append(path);
			fullpath.append(".mrskel");
			skelHandler->Export(fullpath.c_str());

			isRunning = false;

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
	SkeletonAnimation skel;
	Manager manager;
	MrAnimHandler * animHandler = new MrAnimHandler;

	bool isRunning = true;

	while (isRunning)
	{

		std::string name;
		std::string path;

		std::string fullpath = ".\\FBX\\";

		std::cout << "Scene with animation: " << std::endl;
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

			MrKeyFramedJoint * key = new MrKeyFramedJoint[numJoints];


			for (int i = 0; i < numJoints; i++)
			{
				key[i].matrix = new glm::mat4[numKeys];
				key[i].keyFrames = new int32_t[numKeys];
			}

			int count = 0;
			for (int i = 0; i < numJoints; i++)
			{
				for (int j = 0; j < numKeys; j++)
				{
					glm::mat4 posMat = glm::translate(skel.GetTransformationMatrices()[count]);

					glm::mat4 xRot = glm::rotate(glm::radians(skel.GetRotationMatrices()[count].x), glm::vec3(1.0, 0.0, 0.0));
					glm::mat4 yRot = glm::rotate(glm::radians(skel.GetRotationMatrices()[count].y), glm::vec3(0.0, 1.0, 0.0));
					glm::mat4 zRot = glm::rotate(glm::radians(skel.GetRotationMatrices()[count].z), glm::vec3(0.0, 0.0, 1.0));

					glm::mat4 rotMat = zRot * yRot * xRot;

					glm::mat4 scaleMat = glm::scale(skel.GetScalingMatrices()[count]);

					glm::mat4 mat = posMat * rotMat * scaleMat;

					key[i].keyFrames[j] = 0;
					key[i].matrix[j] = mat;
					key[i].jointID = 0;
					key[i].numKeyframes = numKeys;
					count++;
				}
			}

			animHandler->SetName(name.c_str());

			animHandler->SetKeyframedJoint(key);
			animHandler->SetNumKeyFramedJoints(numJoints);
			animHandler->SetFirstKeyFrame(1);
			animHandler->SetLastKeyFrame(numKeys);


			std::string fullpath = ".\\Assets\\Skeletons\\";

			std::cout << "Name: " << std::endl;
			std::cout << "INPUT :: .\\Assets\\Skeletons\\";
			std::getline(std::cin, path);
			fullpath.append(path);
			fullpath.append(".mranim");
			animHandler->Export(fullpath.c_str());

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


void SuperExporter::AddMaterial()
{
	int nrOfTextures = 1;

	MrTexture * textures = new MrTexture[nrOfTextures];

	std::string fullpath = ".\\FBX\\";
	std::string path;

	std::cout << "Texture path: " << std::endl;
	std::cout << "INPUT :: .\\FBX\\";
	std::getline(std::cin, path);
	fullpath.append(path);

	for (int i = 0; i < nrOfTextures; i++)
	{
		int width, height, numComponents;
		unsigned char * imageData = stbi_load(fullpath.c_str(), &width, &height, &numComponents, STBI_rgb_alpha);

		textures[i].type = ALBEDO_MAP;
		textures[i].width = (uint32_t)width;
		textures[i].height = (uint32_t)height;
		textures[i].numComponents = numComponents;
		textures[i].dataLength = width * height * (numComponents + 1); //sizeof(imageData) / sizeof(imageData[1]);

		textures[i].data = new unsigned char[textures[i].dataLength];

		for (int j = 0; j < textures[i].dataLength; j++)
		{
			textures[i].data[j] = imageData[j];
		}


		if (imageData == nullptr)
		{
			return;
		}

		textures[i].data = imageData;
	}

	MrMatHandler * mat = new MrMatHandler;
	mat->SetTextures(textures, nrOfTextures);


	fullpath = ".\\Assets\\Materials\\";

	std::cout << "Name: " << std::endl;
	std::cout << "INPUT :: .\\Assets\\Materials\\";
	std::getline(std::cin, path);
	fullpath.append(path);
	fullpath.append(".mrmat");
	mat->Export(fullpath.c_str());

	delete mat;
}

void SuperExporter::AddCamera()
{
	std::string fullpath = ".\\FBX\\";
	std::string path;

	Manager manager;
	CameraInfo target;
	MrCameraHandler * cameraHandler = new MrCameraHandler;
	std::cout << "Camera path: " << std::endl;
	std::cout << "INPUT :: .\\FBX\\";
	std::getline(std::cin, path);
	fullpath.append(path);

	manager.Init(fullpath.c_str());
	manager.Run(target);
	MrCamera* camera = new MrCamera[target.getCameraArray().size()];

	for (int i = 0; i < target.getCameraArray().size(); i++)
	{
		camera[i].m_aspectRatio = target.getCameraArray().at(i).GetAspectRatio();
		camera[i].m_farPlane = target.getCameraArray().at(i).GetFarPlane();
		camera[i].m_FOV = target.getCameraArray().at(i).GetFOV();
		camera[i].m_lookAt = target.getCameraArray().at(i).GetLookAt();
		camera[i].m_nearPlane = target.getCameraArray().at(i).GetNearPlane();
		camera[i].m_position = target.getCameraArray().at(i).GetPosition();
		camera[i].m_upVector = target.getCameraArray().at(i).GetUpVector();
		target.PrintCamera0Info(i);
	}

	cameraHandler->SetCameras(camera, target.getCameraArray().size());

	fullpath = ".\\Assets\\Camera\\";
	std::cout << "Name: " << std::endl;
	std::cout << "INPUT :: .\\Assets\\Camera\\";
	std::getline(std::cin, path);
	fullpath.append(path);
	fullpath.append(".mrcamera");
	cameraHandler->Export(fullpath.c_str());


	delete cameraHandler;
}

void SuperExporter::AddLight()
{
	std::string fullpath = ".\\FBX\\";
	std::string path;

	Manager manager;
	LightHandler target;
	MrLightHandler* lightHandler = new MrLightHandler;

	std::cout << "Light path: " << std::endl;
	std::cout << "INPUT :: .\\FBX\\";
	std::getline(std::cin, path);
	fullpath.append(path);

	manager.Init(fullpath.c_str());
	manager.Run(target);
	MrLight* light = new MrLight[target.GetLights().size()];

	for (int i = 0; i < target.GetLights().size(); i++)
	{
		light[i].m_color = target.GetLights().at(i).GetColor();
		light[i].m_dirVec = target.GetLights().at(i).GetDirection();
		light[i].m_pos = target.GetLights().at(i).GetPos();
		light[i].m_scale = target.GetLights().at(i).GetScale();
		light[i].m_type = target.GetLights().at(i).GetType();
	}

	lightHandler->SetLights(light, target.GetLights().size());

	fullpath = ".\\Assets\\Light\\";
	std::cout << "Name: " << std::endl;
	std::cout << "INPUT :: .\\Assets\\Light\\";
	std::getline(std::cin, path);
	fullpath.append(path);
	fullpath.append(".mrlight");
	lightHandler->Export(fullpath.c_str());

	delete lightHandler;

}


void SuperExporter::Material()
{
	// Do something...
}


void SuperExporter::CalculateTangents(VertexInfo & vertInfo, std::vector<glm::vec3> & tangents, std::vector<glm::vec3> & biTangents)
{
	for (int i = 0; i < vertInfo.GetPos().size(); i++)
	{
		glm::vec3 v0 = vertInfo.GetPos()[vertInfo.GetIndices()[i]];
		glm::vec3 v1 = vertInfo.GetPos()[vertInfo.GetIndices()[i] + 1];
		glm::vec3 v2 = vertInfo.GetPos()[vertInfo.GetIndices()[i] + 2];

		glm::vec2 uv0 = vertInfo.GetUV()[vertInfo.GetIndices()[i]];
		glm::vec2 uv1 = vertInfo.GetUV()[vertInfo.GetIndices()[i + 1]];
		glm::vec2 uv2 = vertInfo.GetUV()[vertInfo.GetIndices()[i + 2]];

		glm::vec3 deltaPos1 = v1 - v0;
		glm::vec3 deltaPos2 = v2 - v0;

		glm::vec2 deltaUV1 = uv1 - uv0;
		glm::vec2 deltaUV2 = uv2 - uv0;

		float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);

		glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y)*r;

		glm::vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x)*r;

		tangents.push_back(tangent);
		biTangents.push_back(bitangent);
	}
}
