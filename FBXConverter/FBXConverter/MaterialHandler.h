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
	MaterialHandler();
	virtual ~MaterialHandler();

	void ImportMaterial(FbxNode * pNode);

private:
	struct Material
	{
		glm::vec3 m_ambient;
		glm::vec3 m_diffuse;
		glm::vec3 m_emissive;
		float	  m_opacity;
		std::string	m_textureFilePath;
	};
	std::vector<Material> m_materials;
};

#endif // !__MATERIALHANDLER_H__