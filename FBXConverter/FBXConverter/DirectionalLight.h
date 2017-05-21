#ifndef __DIRECTIONALLIGHT_H__
#define __DIRECTIONALLIGHT_H__

#define FBXSDK_SHARED

#include <fbxsdk.h>
#include <glm.hpp>

class DirectionalLight
{
public:
	DirectionalLight();
	virtual ~DirectionalLight();

	void SaveData(FbxNode* node);
	bool IsLight();

private:
	glm::vec3 m_dirVec;
	bool m_isLight;

};

#endif // !__DIRECTIONALLIGHT_H__