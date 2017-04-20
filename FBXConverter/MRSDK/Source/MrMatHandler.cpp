#include "MrMatHandler.h"


namespace mr
{
	//::.. CONSTURCTORS ..:://
	MrMatHandler::MrMatHandler()
	{
		Init();
	}


	MrMatHandler::~MrMatHandler()
	{
	}


	//::.. IMPORT/EXPORT ..:://
	bool MrMatHandler::Import(const char * filepath)
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

		m_textures = new MrTexture[m_numTextures];

		for (uint32_t i = 0; i < m_numTextures; i++)
		{
			file.read(reinterpret_cast<char*>(&m_textures[i].textureFlag), sizeof(uint32_t));
			file.read(reinterpret_cast<char*>(&m_textures[i].numComponents), sizeof(uint32_t));
			file.read(reinterpret_cast<char*>(&m_textures[i].width), sizeof(int32_t));
			file.read(reinterpret_cast<char*>(&m_textures[i].height), sizeof(int32_t));

			// Size.
			uint32_t size = static_cast<uint32_t>(m_textures[i].numComponents * m_textures[i].width * m_textures[i].height);

			m_textures[i].data = new int32_t[size];

			file.read(reinterpret_cast<char*>(m_textures[i].data), sizeof(int32_t) * size);

		}

		// Close file.
		file.close();

		m_isLoaded = true;

		return true;
	}


	bool MrMatHandler::Export(const char * filepath)
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
			file.write(reinterpret_cast<char*>(&m_textures[i].textureFlag), sizeof(uint32_t));
			file.write(reinterpret_cast<char*>(&m_textures[i].numComponents), sizeof(uint32_t));
			file.write(reinterpret_cast<char*>(&m_textures[i].width), sizeof(int32_t));
			file.write(reinterpret_cast<char*>(&m_textures[i].height), sizeof(int32_t));

			// Size.
			uint32_t size = static_cast<uint32_t>(m_textures[i].numComponents * m_textures[i].width * m_textures[i].height);
			file.write(reinterpret_cast<char*>(m_textures[i].data), sizeof(int32_t) * size);
			
		}

		file.close();

		return true;
	}


	void MrMatHandler::Free()
	{
		if (!m_isLoaded)
		{
			return;
		}

		for (uint32_t i = 0; i < m_numTextures; i++)
		{
			delete[] m_textures[i].data;
		}

		delete[] m_textures;
	}


	//::.. GET FUNCTIONS ..:://
	uint32_t MrMatHandler::GetNumTextures() const
	{
		return uint32_t();
	}


	MrTexture * MrMatHandler::GetTextures() const
	{
		return nullptr;
	}


	//::.. SET FUNCTIONS ..:://
	void MrMatHandler::SetNumTextures(uint32_t numTextures)
	{
		m_numTextures = numTextures;
	}


	void MrMatHandler::SetTextures(MrTexture * textures)
	{
		m_textures = textures;
	}


	//::.. HELP FUNCTIONS ..:://
	void MrMatHandler::Init()
	{
		m_isLoaded = false;

		m_numTextures = 0;

		m_textures = nullptr;
	}
}