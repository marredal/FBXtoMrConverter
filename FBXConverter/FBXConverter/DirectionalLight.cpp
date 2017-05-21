#include "DirectionalLight.h"



DirectionalLight::DirectionalLight()
{
}


DirectionalLight::~DirectionalLight()
{
}

void DirectionalLight::SaveData(FbxNode* node)
{
	m_isLight = false;
	FbxLight* light = node->GetLight();

	if (light->LightType.Get() == FbxLight::eDirectional)
	{
		float dirX = light->GetNode(0)->LclRotation.Get()[0];
		float dirY = light->GetNode(0)->LclRotation.Get()[1];
		float dirZ = light->GetNode(0)->LclRotation.Get()[2];

		m_dirVec = glm::vec3(dirX, dirY, dirZ);

		m_isLight = true;
	}

}

bool DirectionalLight::IsLight()
{
	return m_isLight;
}
