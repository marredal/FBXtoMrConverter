#include "LightHandler.h"



LightHandler::LightHandler()
{
}


LightHandler::~LightHandler()
{
}

void LightHandler::SaveData(FbxNode * node)
{
	SaveAllNodes(node);

	Light light;

	for (int i = 0; i < m_nodes.size(); i++)
	{
		light.SaveData(m_nodes[i]);

		if (light.IsLight())
		{
			m_lights.push_back(light);
		}
	}

	m_nodes.clear();
}

void LightHandler::SaveAllNodes(FbxNode * node)
{
	if (node)
	{
		if (node->GetNodeAttribute())
		{
			FbxLight* light = node->GetLight();
			if (light != NULL)
			{
				m_nodes.push_back(node);
				for (int i = 0; i < node->GetChildCount(); i++)
				{
					SaveAllNodes(node->GetChild(i));
				}
			}
		}
	}

}

std::vector<Light> LightHandler::GetLights()
{
	return m_lights;
}
