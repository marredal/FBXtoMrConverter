#pragma once


#include "MrUtility.h"
#include "MrMeshHandler.h"
#include "MrSkelHandler.h"
#include "MrAnimHandler.h"


#include <cstring>
#include <cstdint>


#if DLLEXPORT
#define DLL __declspec(dllexport)
#else
#define DLL __declspec(dllimport)
#endif


class MrHandler
{
public:
	//::.. CONSTRUCTORS ..:://
	MrHandler();
	virtual ~MrHandler();

	//::.. IMPORT/EXPORT ..:://
	bool Import(const char * filepath);
	bool Export();

	void Free();

	//::.. GET FUNCTIONS ..:://
	const char * GetName();
	uint32_t GetNumMeshHandlers();
	uint32_t GetNumSkelHandlers();
	uint32_t GetNumAnimHandlers();
	MrMeshHandler * GetMeshHandlers();
	MrSkelHandler * GetSkelHandlers();
	MrAnimHandler * GetAnimHandlers();
	const char ** GetMeshFilePaths();
	const char ** GetSkelFilePaths();
	const char ** GetAnimFilePaths();

	//::.. SET FUNCTIONS ..:://
	void SetName(const char * name);
	void SetMeshHandlers(MrMeshHandler * meshHandlers, uint32_t num);
	void SetSkelHandlers(MrSkelHandler * skelHandlers, uint32_t num);
	void SetAnimHandlers(MrAnimHandler * animHandlers, uint32_t num);

private:
	//::.. HELP FUNCTIONS ..:://
	void Init();

private:
	bool			m_isLoaded;

	const char *	m_name;

	const char **	m_meshFilePaths;
	const char **	m_skelFilePaths;
	const char **	m_animFilePaths;

	uint32_t		m_numMeshHandlers;
	uint32_t		m_numSkelHandlers;
	uint32_t		m_numAnimHandlers;

	MrMeshHandler * m_meshHandler;
	MrSkelHandler * m_skelHandler;
	MrAnimHandler * m_animHandler;
};



inline MrHandler::MrHandler()
{
	Init();
}

inline MrHandler::~MrHandler()
{
}

inline bool MrHandler::Import(const char * filepath)
{
	return false;
}

inline bool MrHandler::Export()
{
	// Project folder structure.
	std::string filepath = ".\\Assets\\Prefabs\\";
	std::string filepathMeshes = ".\\Assets\\Meshes\\";
	std::string filepathSkel = ".\\Assets\\Skeletons\\";
	std::string filepathAnim = ".\\Assets\\Animations\\";

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
			file.write(reinterpret_cast<char*>(&path[j]), sizeof(char));
		}

		m_meshHandler->Export(path.c_str());
	}


	// Skeletons.
	file.write(reinterpret_cast<char*>(&m_numSkelHandlers), sizeof(uint32_t));

	for (uint32_t i = 0; i < m_numSkelHandlers; i++)
	{
		// GET NAME
		std::string path = filepathSkel + m_name + ".mrskel";

		uint32_t strLenght = path.length();

		file.write(reinterpret_cast<char*>(&strLenght), sizeof(uint32_t));

		for (uint32_t j = 0; j < strLenght; j++)
		{
			file.write(reinterpret_cast<char*>(&path[j]), sizeof(char));
		}

		m_skelHandler->Export(path.c_str());
	}


	// Animations.
	file.write(reinterpret_cast<char*>(&m_numAnimHandlers), sizeof(uint32_t));

	for (uint32_t i = 0; i < m_numAnimHandlers; i++)
	{
		std::string path = filepathAnim + m_name + "@" + ".mranim";

		uint32_t strLenght = path.length();

		file.write(reinterpret_cast<char*>(&strLenght), sizeof(uint32_t));

		for (uint32_t j = 0; j < strLenght; j++)
		{
			file.write(reinterpret_cast<char*>(&path[j]), sizeof(char));
		}

		m_animHandler->Export(path.c_str());
	}

	// Close the file.
	file.close();

	return true;
}


inline void MrHandler::Free()
{
	if (!m_isLoaded)
	{
		return;
	}

	//		delete[] m_meshHandler;
	//		delete[] m_skelHandler;
	//		delete[] m_animHandler;

	Init();
}


inline const char * MrHandler::GetName()
{
	return m_name;
}


//::.. GET FUNCTIONS ..:://
inline uint32_t MrHandler::GetNumMeshHandlers()
{
	return m_numMeshHandlers;
}


inline uint32_t MrHandler::GetNumSkelHandlers()
{
	return m_numSkelHandlers;
}


inline uint32_t MrHandler::GetNumAnimHandlers()
{
	return m_numAnimHandlers;
}


inline MrMeshHandler * MrHandler::GetMeshHandlers()
{
	return m_meshHandler;
}


inline MrSkelHandler * MrHandler::GetSkelHandlers()
{
	return m_skelHandler;
}


inline MrAnimHandler * MrHandler::GetAnimHandlers()
{
	return m_animHandler;
}

inline const char ** MrHandler::GetMeshFilePaths()
{
	return m_meshFilePaths;
}

inline const char ** MrHandler::GetSkelFilePaths()
{
	return m_skelFilePaths;
}

inline const char ** MrHandler::GetAnimFilePaths()
{
	return m_animFilePaths;
}


//::.. SET FUNCTIONS ..:://
inline void MrHandler::SetName(const char * name)
{
	m_name = name;
	m_isLoaded = true;
}


inline void MrHandler::SetMeshHandlers(MrMeshHandler * meshHandlers, uint32_t num)
{
	m_numMeshHandlers = num;
	m_meshHandler = meshHandlers;
	m_isLoaded = true;
}


inline void MrHandler::SetSkelHandlers(MrSkelHandler * skelHandlers, uint32_t num)
{
	m_numSkelHandlers = num;
	m_skelHandler = skelHandlers;
	m_isLoaded = true;
}


inline void MrHandler::SetAnimHandlers(MrAnimHandler * animHandlers, uint32_t num)
{
	m_numAnimHandlers = num;
	m_animHandler = animHandlers;
	m_isLoaded = true;
}


//::.. HELP FUNCTIONS ..:://
inline void MrHandler::Init()
{
	m_isLoaded = false;

	m_numMeshHandlers = 0;
	m_numSkelHandlers = 0;
	m_numAnimHandlers = 0;

	m_meshHandler = nullptr;
	m_skelHandler = nullptr;
	m_animHandler = nullptr;
}
