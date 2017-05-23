#ifndef __LIGHTHANDLER_H__
#define __LIGHTHANDLER_H__

#include "Light.h"
#include <vector>




class LightHandler
{
public:
	LightHandler();
	virtual ~LightHandler();

	void SaveData(FbxNode * node);
	void SaveAllNodes(FbxNode * node);
	std::vector<Light> GetLights();

private:
	std::vector<Light> m_lights;
	std::vector<FbxNode*> m_nodes;
	
};

#endif // !__LIGHTHANDLER_H__