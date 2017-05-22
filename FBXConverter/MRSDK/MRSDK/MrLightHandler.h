#pragma once


#include <fstream>
#include <cstdint>
#include <glm.hpp>


enum MrLightType
{
	DIRECTIONAL = 0,
	SPOT,
	POINT
};


struct MrLight
{
	glm::vec3 m_dirVec;
	glm::vec3 m_pos;
	glm::vec3 m_scale;
	glm::vec3 m_color;
	int		  m_type;
};


class MrLightHandler
{
public:

	//::.. CONSTRUCTORS ..:://
	MrLightHandler();
	virtual ~MrLightHandler();

	//::.. IMPORT/EXPORT ..:://
	bool Import(const char* filepath);
	bool Export(const char* filepath);

	void Free();

	//::.. GET FUNCTIONS ..:://
	uint32_t GetNumLights();
	MrLight * GetLights();

	//::.. SET FUNCTIONS ..:://
	void SetLights(MrLight * lights, uint32_t numLights);

private:
	//::.. HELP FUNCTIONS ..:://
	void Init();

private:
	bool		m_isLoaded;

	uint32_t	m_numLights;
	MrLight *	m_lights;
};


inline MrLightHandler::MrLightHandler()
{
	Init();
}


inline MrLightHandler::~MrLightHandler()
{
	Free();
}


inline bool MrLightHandler::Import(const char * filepath)
{
	if (m_isLoaded)
	{
		Free();
	}

	std::ifstream file(filepath, std::ios::binary);

	if (!file.is_open())
	{
		return false;
	}

	file.read(reinterpret_cast<char*>(&m_numLights), sizeof(uint32_t));

	m_lights = new MrLight[m_numLights];
	file.read(reinterpret_cast<char*>(m_lights), sizeof(MrLight) * m_numLights);

	file.close();

	return true;
}


inline bool MrLightHandler::Export(const char * filepath)
{
	std::ofstream file(filepath, std::ios::binary);

	if (!file.is_open())
	{
		return false;
	}

	file.write(reinterpret_cast<char*>(&m_numLights), sizeof(uint32_t));
	file.write(reinterpret_cast<char*>(m_lights), sizeof(MrLight) * m_numLights);

	file.close();

	return true;
}


inline void MrLightHandler::Free()
{
	// TODO
}


inline uint32_t MrLightHandler::GetNumLights()
{
	return uint32_t();
}


inline MrLight * MrLightHandler::GetLights()
{
	return m_lights;
}


inline void MrLightHandler::SetLights(MrLight * lights, uint32_t numLights)
{
	m_lights = lights;
	m_numLights = numLights;
	m_isLoaded = true;
}


//::.. HELP FUNCTIONS ..:://
inline void MrLightHandler::Init()
{

}
