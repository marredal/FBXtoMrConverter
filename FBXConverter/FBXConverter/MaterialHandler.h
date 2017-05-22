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
	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_emissive;
	float	  m_opacity;
	std::string	m_textureFilePath;
	std::string	m_normalFilePath;
	std::string	m_specularFilePath;
	int			nrOfTextures;
	int			nrOfNormalMaps;
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