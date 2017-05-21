#include "Light.h"



Light::Light()
{
}


Light::~Light()
{
}

void Light::SaveData(FbxNode* node)
{
	m_isLight = false;
	FbxLight* light = node->GetLight();

	if (light->LightType.Get() == FbxLight::eDirectional)
	{
		float dirX = light->GetNode(0)->LclRotation.Get()[0];
		float dirY = light->GetNode(0)->LclRotation.Get()[1];
		float dirZ = light->GetNode(0)->LclRotation.Get()[2];

		m_dirVec = glm::vec3(dirX, dirY, dirZ);
		
		m_color = glm::vec3(light->Color.Get()[0], light->Color.Get()[1], light->Color.Get()[2]);

		m_isLight = true;

	}
	if (light->LightType.Get() == FbxLight::ePoint)
	{
		float posX = light->GetNode(0)->LclTranslation.Get()[0];
		float posY = light->GetNode(0)->LclTranslation.Get()[1];
		float posZ = light->GetNode(0)->LclTranslation.Get()[2];

		m_pos = glm::vec3(posX, posY, posZ);
		
		m_color = glm::vec3(light->Color.Get()[0], light->Color.Get()[1], light->Color.Get()[2]);

		m_isLight = true;


	}
	if (light->LightType.Get() == FbxLight::eSpot)
	{
		float dirX = light->GetNode(0)->LclRotation.Get()[0];
		float dirY = light->GetNode(0)->LclRotation.Get()[1];
		float dirZ = light->GetNode(0)->LclRotation.Get()[2];

		m_dirVec = glm::vec3(dirX, dirY, dirZ);

		float posX = light->GetNode(0)->LclTranslation.Get()[0];
		float posY = light->GetNode(0)->LclTranslation.Get()[1];
		float posZ = light->GetNode(0)->LclTranslation.Get()[2];

		m_pos = glm::vec3(posX, posY, posZ);

		m_color = glm::vec3(light->Color.Get()[0], light->Color.Get()[1], light->Color.Get()[2]);

		m_isLight = true;
	}

}

bool Light::IsLight()
{
	return m_isLight;
}
