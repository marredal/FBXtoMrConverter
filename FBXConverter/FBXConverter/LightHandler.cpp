#include "LightHandler.h"



LightHandler::LightHandler()
{
}


LightHandler::~LightHandler()
{
}

void LightHandler::SaveData(FbxNode * node)
{
	Light light;

	light.SaveData(node);

	if (light.IsLight())
	{
		m_lights.push_back(light);
	}
}

std::vector<Light> LightHandler::GetLights()
{
	return m_lights;
}
