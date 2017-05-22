#ifndef __MATERIALHANDLER_H__
#define __MATERIALHANDLER_H__
#define FBXSDK_SHARED

#include <fbxsdk.h>
#include <glm.hpp>
#include <vector>
#pragma comment(lib, "libfbxsdk.lib")
#include <iostream>

class MaterialHandler
{
public:
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

	MaterialHandler();
	virtual ~MaterialHandler();

	void ImportMaterial(FbxNode * pNode);

	Material GetMaterial(int i);
	int32_t	GetNumMaterials();

private:
	std::vector<Material> m_materials;
};

#endif // !__MATERIALHANDLER_H__