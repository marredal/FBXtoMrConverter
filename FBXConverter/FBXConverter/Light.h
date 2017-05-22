#ifndef __DIRECTIONALLIGHT_H__
#define __DIRECTIONALLIGHT_H__

#define FBXSDK_SHARED

#include <fbxsdk.h>
#include <glm.hpp>

class Light
{
public:
	Light();
	virtual ~Light();

	void SaveData(FbxNode* node);
	bool IsLight();

	//::..Get Functions..:://


private:

	enum TYPE
	{
		DIRECTIONAL_LIGHT,
		POINT_LIGHT,
		SPOT_LIGHT
	};

	glm::vec3 m_dirVec;
	glm::vec3 m_pos;
	glm::vec3 m_scale;
	bool	  m_isLight;
	int		  m_type;
	glm::vec3 m_color;

};

#endif // !__DIRECTIONALLIGHT_H__