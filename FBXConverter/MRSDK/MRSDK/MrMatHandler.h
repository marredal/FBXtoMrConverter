#pragma once


#include <fstream>
#include <cstdint>
#include <glm.hpp>


enum MrTextureType
{
	ALBEDO_MAP = 0,
	NORMAL_MAP,
	SPEC_MAP
};


struct MrTexture
{
	uint32_t		type;
	uint32_t		width;
	uint32_t		height;
	uint32_t		numComponents;
	uint32_t		dataLength;
	unsigned char *	data;
};


class MrMatHandler
{
public:
	//::.. CONSTRUCTORS ..:://
	MrMatHandler();
	virtual ~MrMatHandler();

	//::.. IMPORT/EXPORT ..:://
	bool Import(const char* filepath);
	bool Export(const char* filepath);

	void Free();

	//::.. GET FUNCTIONS ..:://
	uint32_t GetNumTextures();
	MrTexture * GetTextures();
	glm::vec3 GetAmbient();
	glm::vec3 GetDiffuse();
	glm::vec3 GetEmissive();
	float GetOpacity();

	//::.. SET FUNCTIONS ..:://
	void SetTextures(MrTexture * textures, uint32_t num);

private:
	//::.. HELP FUNCTIONS ..:://
	void Init();

private:
	bool			m_isLoaded;

	uint32_t		m_numTextures;
	MrTexture *		m_textures;
	glm::vec3		m_ambient;
	glm::vec3		m_diffuse;
	glm::vec3		m_emissive;
	float			m_opacity;
};


inline MrMatHandler::MrMatHandler()
{
	Init();
}


inline MrMatHandler::~MrMatHandler()
{
}


//::.. IMPORT/EXPORT ..:://
inline bool MrMatHandler::Import(const char * filepath)
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

	file.read(reinterpret_cast<char*>(&m_numTextures), sizeof(uint32_t));

	for (uint32_t i = 0; i < m_numTextures; i++)
	{
		file.read(reinterpret_cast<char*>(&m_textures[i].type), sizeof(uint32_t));
		file.read(reinterpret_cast<char*>(&m_textures[i].width), sizeof(uint32_t));
		file.read(reinterpret_cast<char*>(&m_textures[i].height), sizeof(uint32_t));
		file.read(reinterpret_cast<char*>(&m_textures[i].numComponents), sizeof(uint32_t));
		file.read(reinterpret_cast<char*>(&m_textures[i].dataLength), sizeof(uint32_t));
		file.read(reinterpret_cast<char*>(m_textures[i].data), sizeof(unsigned char) * m_textures[i].dataLength);
	}

	file.close();

	return true;
}


inline bool MrMatHandler::Export(const char * filepath)
{
	if (!m_isLoaded)
	{
		return false;
	}

	std::ofstream file(filepath, std::ios::binary);

	if (!file.is_open())
	{
		return false;
	}

	file.write(reinterpret_cast<char*>(&m_numTextures), sizeof(uint32_t));

	for (uint32_t i = 0; i < m_numTextures; i++)
	{
		file.write(reinterpret_cast<char*>(&m_textures[i].type), sizeof(uint32_t));
		file.write(reinterpret_cast<char*>(&m_textures[i].width), sizeof(uint32_t));
		file.write(reinterpret_cast<char*>(&m_textures[i].height), sizeof(uint32_t));
		file.write(reinterpret_cast<char*>(&m_textures[i].numComponents), sizeof(uint32_t));
		file.write(reinterpret_cast<char*>(&m_textures[i].dataLength), sizeof(uint32_t));
		file.write(reinterpret_cast<char*>(m_textures[i].data), sizeof(unsigned char) * m_textures[i].dataLength);
	}

	file.close();

	return true;
}


inline void MrMatHandler::Free()
{
	// TODO
}


inline uint32_t MrMatHandler::GetNumTextures()
{
	return uint32_t();
}


inline MrTexture * MrMatHandler::GetTextures()
{
	return m_textures;
}


inline void MrMatHandler::SetTextures(MrTexture * textures, uint32_t num)
{
	m_textures = textures;
	m_numTextures = num;
	m_isLoaded = true;
}


//::.. HELP FUNCTIONS ..:://
inline void MrMatHandler::Init()
{
	m_isLoaded			= false;

	m_textures			= nullptr;
}
