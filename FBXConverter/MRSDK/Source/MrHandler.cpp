#include "MrHandler.h"



namespace MR
{
	//::.. CONSTRUCTORS ..:://
	MrHandler::MrHandler()
	{
	}


	MrHandler::~MrHandler()
	{
		Free();
	}


	//::.. IMPORT/EXPORT ..:://
	bool MrHandler::Import(const char * filepath)
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

		uint32_t version;
		uint32_t subVersion;

		// Version and sub version.
		file.read(reinterpret_cast<char*>(&version), sizeof(uint32_t));
		file.read(reinterpret_cast<char*>(&subVersion), sizeof(uint32_t));


		// Check version.
		if (version < MR_LOWEST_VERSION && subVersion < MR_LOWEST_SUBVERSION)
		{
			file.close();
			return false;
		}


		// Meshes.
		file.read(reinterpret_cast<char*>(&m_numMeshHandlers), sizeof(uint32_t));

		m_meshHandler = new MrMeshHandler[m_numMeshHandlers];

		for (uint32_t i = 0; i < m_numMeshHandlers; i++)
		{
			uint32_t strLenght;
			file.read(reinterpret_cast<char*>(&strLenght), sizeof(uint32_t));

			char * path = new char[strLenght];

			for (uint32_t j = 0; j < strLenght; j++)
			{
				file.read(reinterpret_cast<char*>(path[j]), sizeof(char));
			}

			m_meshHandler[i].Import(path);
		}


		// Skeletons.
		file.read(reinterpret_cast<char*>(&m_numSkelHandlers), sizeof(uint32_t));

		m_skelHandler = new MrSkelHandler[m_numSkelHandlers];

		for (uint32_t i = 0; i < m_numMeshHandlers; i++)
		{
			uint32_t strLenght;
			file.read(reinterpret_cast<char*>(&strLenght), sizeof(uint32_t));

			char * path = new char[strLenght];

			file.read(reinterpret_cast<char*>(&strLenght), sizeof(uint32_t));

			for (uint32_t j = 0; j < strLenght; j++)
			{
				file.read(reinterpret_cast<char*>(path[j]), sizeof(char));
			}

			m_skelHandler->Import(path);
		}


		// Animations.
		file.read(reinterpret_cast<char*>(&m_numAnimHandlers), sizeof(uint32_t));

		m_animHandler = new MrAnimHandler[m_numAnimHandlers];

		for (uint32_t i = 0; i < m_numMeshHandlers; i++)
		{
			uint32_t strLenght;
			file.read(reinterpret_cast<char*>(&strLenght), sizeof(uint32_t));

			char * path = new char[strLenght];

			for (uint32_t j = 0; j < strLenght; j++)
			{
				file.read(reinterpret_cast<char*>(path[j]), sizeof(char));
			}

			m_animHandler[i].Import(path);
		}

		m_isLoaded = true;

		return true;
	}


	bool MrHandler::Export()
	{
		if (!m_isLoaded)
		{
			return false;
		}

		// Project folder structure.
		std::string filepath		= ".\\Assets\\Prefabs\\";
		std::string filepathMeshes	= ".\\Assets\\Meshes\\";
		std::string filepathSkel	= ".\\Assets\\Skeltons\\";
		std::string filepathAnim	= ".\\Assets\\Animations\\";

		filepath.append(m_name);
		filepath.append(".mr");

		std::ofstream file(filepath.c_str(), std::ios::binary);

		if (!file.is_open())
		{
			return false;
		}

		uint32_t version = MR_VERSION;
		uint32_t subVersion = MR_SUBVERSION;

		// Version and sub version.
		file.write(reinterpret_cast<char*>(&version), sizeof(uint32_t));
		file.write(reinterpret_cast<char*>(&subVersion), sizeof(uint32_t));

		// Meshes.
		file.write(reinterpret_cast<char*>(&m_numMeshHandlers), sizeof(uint32_t));

		for (uint32_t i = 0; i < m_numMeshHandlers; i++)
		{
			std::string path = filepathMeshes + m_name + ".mrmesh";

			uint32_t strLenght = path.length();

			file.write(reinterpret_cast<char*>(&strLenght), sizeof(uint32_t));

			for (uint32_t j = 0; j < strLenght; j++)
			{
				file.write(reinterpret_cast<char*>(path[j]), sizeof(char));
			}

			m_meshHandler->Export(path.c_str());
		}


		// Skeletons.
		file.write(reinterpret_cast<char*>(&m_numSkelHandlers), sizeof(uint32_t));

		for (uint32_t i = 0; i < m_numMeshHandlers; i++)
		{
			// GET NAME
			std::string path = filepathSkel + m_name + ".mrskel";

			uint32_t strLenght = path.length();

			file.write(reinterpret_cast<char*>(&strLenght), sizeof(uint32_t));

			for (uint32_t j = 0; j < strLenght; j++)
			{
				file.write(reinterpret_cast<char*>(path[j]), sizeof(char));
			}

			m_skelHandler->Export(path.c_str());
		}


		// Animations.
		file.write(reinterpret_cast<char*>(&m_numAnimHandlers), sizeof(uint32_t));

		for (uint32_t i = 0; i < m_numMeshHandlers; i++)
		{
			std::string path = filepathSkel + m_name + "@" + m_animHandler[i].GetName() + ".mranim";

			uint32_t strLenght = path.length();

			file.write(reinterpret_cast<char*>(&strLenght), sizeof(uint32_t));

			for (uint32_t j = 0; j < strLenght; j++)
			{
				file.write(reinterpret_cast<char*>(path[j]), sizeof(char));
			}

			m_animHandler->Export(path.c_str());
		}

		// Close the file.
		file.close();

		return true;
	}


	void MrHandler::Free()
	{
		if (!m_isLoaded)
		{
			return;
		}

		delete[] m_meshHandler;
		delete[] m_skelHandler;
		delete[] m_animHandler;

		Init();
	}


	const char * MrHandler::GetName()
	{
		return m_name;
	}


	//::.. GET FUNCTIONS ..:://
	uint32_t MrHandler::GetNumMeshHandlers()
	{
		return m_numMeshHandlers;
	}


	uint32_t MrHandler::GetNumSkelHandlers()
	{
		return m_numSkelHandlers;
	}


	uint32_t MrHandler::GetNumAnimHandlers()
	{
		return m_numAnimHandlers;
	}


	MrMeshHandler * MrHandler::GetMeshHandlers()
	{
		return m_meshHandler;
	}


	MrSkelHandler * MrHandler::GetSkelHandlers()
	{
		return m_skelHandler;
	}


	MrAnimHandler * MrHandler::GetAnimHandlers()
	{
		return m_animHandler;
	}


	//::.. SET FUNCTIONS ..:://
	void MrHandler::SetName(const char * name)
	{
		m_name = name;
		m_isLoaded = true;
	}


	void MrHandler::SetMeshHandlers(MrMeshHandler * meshHandlers, uint32_t num)
	{
		m_numMeshHandlers = num;
		m_meshHandler = meshHandlers;
		m_isLoaded = true;
	}


	void MrHandler::SetSkelHandlers(MrSkelHandler * skelHandlers, uint32_t num)
	{
		m_numSkelHandlers = num;
		m_skelHandler = skelHandlers;
		m_isLoaded = true;
	}


	void MrHandler::SetAnimHandlers(MrAnimHandler * animHandlers, uint32_t num)
	{
		m_numAnimHandlers = num;
		m_animHandler = animHandlers;
		m_isLoaded = true;
	}

	//::.. HELP FUNCTIONS ..:://
	void MrHandler::Init()
	{
		m_isLoaded = false;

		m_numMeshHandlers = 0;
		m_numSkelHandlers = 0;
		m_numAnimHandlers = 0;

		m_meshHandler = nullptr;
		m_skelHandler = nullptr;
		m_animHandler = nullptr;
	}
}