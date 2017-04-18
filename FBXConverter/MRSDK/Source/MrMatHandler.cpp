#include "MrMatHandler.h"


namespace MR
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
		return false;
	}


	bool MrMatHandler::Export(const char * filepath)
	{
		return false;
	}


	void MrMatHandler::Free()
	{
		if (!m_isLoaded)
		{
			return;
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