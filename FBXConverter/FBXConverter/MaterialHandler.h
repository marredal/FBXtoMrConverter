#ifndef __MATERIALHANDLER_H__
#define __MATERIALHANDLER_H__
#define FBXSDK_SHARED

#include <fbxsdk.h>
#include <glm.hpp>
#include <vector>
#pragma comment(lib, "libfbxsdk.lib")
#include <iostream>

struct Material
{
	glm::vec3		ambient;
	glm::vec3		diffuse;
	glm::vec3		emissive;
	float			opacity;
	std::string		textureFilePath;
	std::string		normalFilePath;
	std::string		specularFilePath;
	int				nrOfTextures;
	int				nrOfNormalMaps;
};

class MaterialHandler
{
public:

	MaterialHandler();
	virtual ~MaterialHandler();

	void ImportMaterial(FbxNode * pNode);

	std::vector<Material> GetMaterialVector();
	int32_t	GetNumMaterials();

private:
	std::vector<Material> m_materials;
};

#endif // !__MATERIALHANDLER_H__