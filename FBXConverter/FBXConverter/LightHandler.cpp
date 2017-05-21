#include "LightHandler.h"



LightHandler::LightHandler()
{
}


LightHandler::~LightHandler()
{
}

void LightHandler::SaveData(FbxNode * node)
{
	DirectionalLight light;

	light.SaveData(node);

	if (light.IsLight())
	{
		m_lights.push_back(light);
	}
}