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
	glm::vec3 GetDirection();
	int GetType();
	glm::vec3 GetPos();
	glm::vec3 GetScale();
	glm::vec3 GetColor();	


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
	int		  m_type;
	glm::vec3 m_color;

	bool	  m_isLight;
};

#endif // !__DIRECTIONALLIGHT_H__