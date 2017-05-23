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

	if (light != NULL)
	{
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

			float scaleX = light->GetNode(0)->LclScaling.Get()[0];
			float scaleY = light->GetNode(0)->LclScaling.Get()[1];
			float scaleZ = light->GetNode(0)->LclScaling.Get()[2];

			m_pos = glm::vec3(posX, posY, posZ);
			m_dirVec = glm::vec3(dirX, dirY, dirZ);
			m_scale = glm::vec3(scaleX, scaleY, scaleZ);

			m_color = glm::vec3(light->Color.Get()[0], light->Color.Get()[1], light->Color.Get()[2]);

			m_isLight = true;
		}
		for (int i = 0; i < light->GetNodeCount(); i++)
		{
			SaveData(light->GetNode(i));
		}

	}
	else
	{
		return;
	}
}

bool Light::IsLight()
{
	return m_isLight;
}

glm::vec3 Light::GetDirection()
{
	return m_dirVec;
}

int Light::GetType()
{
	return m_type;
}

glm::vec3 Light::GetPos()
{
	return m_pos;
}

glm::vec3 Light::GetScale()
{
	return m_scale;
}

glm::vec3 Light::GetColor()
{
	return m_color;
}
