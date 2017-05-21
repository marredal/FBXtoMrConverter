#pragma once


#include <MrUtility.h>
#include <fstream>
#include <glm.hpp>


#if DLLEXPORT
#define DLL __declspec(dllexport)
#else
#define DLL __declspec(dllimport)
#endif



class MrSkelHandler
{
public:
	//::.. CONSTURCTORS ..:://
	MrSkelHandler();
	virtual ~MrSkelHandler();

	//::.. IMPORT/EXPORT ..:://
	bool Import(const char * filepath);
	bool Export(const char * filepath);

	void Free();

	//::.. GET FUNCTIONS ..:://
	uint32_t GetNumJoints();
	glm::mat4 * GetMatrix();
	uint32_t * GetParentIDs();
	uint32_t * GetIDs();

	//::.. SET FUNCTIONS ..:://
	void SetNumJoints(uint32_t numJoints);
	void SetMatrix(glm::mat4 * mat);
	void SetParentIDs(uint32_t * parentIDs);
	void SetIDs(uint32_t * ids);

private:
	//::.. HELP FUNCTIONS ..:://
	void Init();

private:
	bool			m_isLoaded;

	uint32_t		m_numJoints;

	glm::mat4 *		m_matrix;
	uint32_t *		m_parentIDs;
	uint32_t *		m_ids;
};



inline MrSkelHandler::MrSkelHandler()
{
	m_isLoaded = false;

	m_numJoints = 0;

	m_matrix = nullptr;
	m_parentIDs = nullptr;
}


inline MrSkelHandler::~MrSkelHandler()
{
	Free();
}


inline bool MrSkelHandler::Import(const char * filepath)
{
	std::ifstream file(filepath, std::ios::binary);

	if (!file.is_open())
	{
		return false;
	}

	file.read(reinterpret_cast<char*>(&m_numJoints), sizeof(uint32_t));
	
	m_matrix = new glm::mat4[m_numJoints];
	m_ids = new uint32_t[m_numJoints];
	m_parentIDs = new uint32_t[m_numJoints];
	
	file.read(reinterpret_cast<char*>(m_matrix), sizeof(glm::mat4) * m_numJoints);
	file.read(reinterpret_cast<char*>(m_ids), sizeof(uint32_t) * m_numJoints);
	file.read(reinterpret_cast<char*>(m_parentIDs), sizeof(uint32_t) * m_numJoints);

	file.close();

	return true;
}

inline bool MrSkelHandler::Export(const char * filepath)
{
	std::ofstream file(filepath, std::ios::binary);

	if (!file.is_open())
	{
		return false;
	}

	file.write(reinterpret_cast<char*>(&m_numJoints), sizeof(uint32_t));

	file.write(reinterpret_cast<char*>(m_matrix), sizeof(glm::mat4) * m_numJoints);
	file.write(reinterpret_cast<char*>(m_ids), sizeof(uint32_t) * m_numJoints);
	file.write(reinterpret_cast<char*>(m_parentIDs), sizeof(uint32_t) * m_numJoints);

	file.close();

	return true;
}

inline void MrSkelHandler::Free()
{
	if (!m_isLoaded)
	{
		return;
	}

	delete m_matrix;
	delete m_parentIDs;

	m_isLoaded = false;

	m_numJoints = 0;

	m_matrix = nullptr;
	m_parentIDs = nullptr;

}


//::.. GET FUNCTIONS ..:://
inline uint32_t MrSkelHandler::GetNumJoints()
{
	return m_numJoints;
}


inline glm::mat4 * MrSkelHandler::GetMatrix()
{
	return m_matrix;
}


inline uint32_t * MrSkelHandler::GetParentIDs()
{
	return m_parentIDs;
}


inline uint32_t * MrSkelHandler::GetIDs()
{
	return m_ids;
}


//::.. SET FUNCTIONS ..:://
inline void MrSkelHandler::SetNumJoints(uint32_t numJoints)
{
	m_numJoints = numJoints;
	m_isLoaded = true;
}


inline void MrSkelHandler::SetMatrix(glm::mat4 * mat)
{
	m_matrix = mat;
	m_isLoaded = true;
}


inline void MrSkelHandler::SetParentIDs(uint32_t * parentIDs)
{
	m_parentIDs = parentIDs;
	m_isLoaded = true;
}


inline void MrSkelHandler::SetIDs(uint32_t * ids)
{
	m_ids = ids;
	m_isLoaded = true;
}


//::.. HELP FUNCTIONS ..:://
inline void MrSkelHandler::Init()
{
	m_isLoaded = false;

	m_numJoints = 0;

	m_matrix = nullptr;
	m_parentIDs = nullptr;
	m_ids = nullptr;
}
