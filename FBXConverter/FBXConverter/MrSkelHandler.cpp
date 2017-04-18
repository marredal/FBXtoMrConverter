#include "MrSkelHandler.h"



MrSkelHandler::MrSkelHandler()
{
	m_isLoaded = false;

	m_numJoints = 0;

	m_matrix = nullptr;
	m_parentIDs = nullptr;
}


MrSkelHandler::~MrSkelHandler()
{
	Free();
}

bool MrSkelHandler::Import(const char * filepath)
{
	if (m_isLoaded)
	{
		Free();
	}

	std::ofstream file(filepath, std::ios::binary);

	if (!file.is_open)
	{
		return false;
	}

	file.write(reinterpret_cast<char*>(&m_numJoints), sizeof(uint32_t));
	file.write(reinterpret_cast<char*>(m_matrix), sizeof(glm::mat4) * m_numJoints);
	file.write(reinterpret_cast<char*>(m_parentIDs), sizeof(uint32_t) * m_numJoints);

	file.close();

	return true;
}

bool MrSkelHandler::Export(const char * filepath, uint32_t numJoints, 
	glm::mat4 * mat, uint32_t * parentIDs)
{
	std::ofstream file(filepath, std::ios::binary);

	if (!file.is_open)
	{
		return false;
	}

	file.write(reinterpret_cast<char*>(&numJoints), sizeof(uint32_t));
	file.write(reinterpret_cast<char*>(mat), sizeof(glm::mat4) * numJoints);
	file.write(reinterpret_cast<char*>(parentIDs), sizeof(uint32_t) * numJoints);

	file.close();

	return true;
}

void MrSkelHandler::Free()
{
	if (!m_isLoaded)
	{
		return;
	}
	
	delete[] m_matrix;
	delete[] m_parentIDs;

	m_isLoaded = false;

	m_numJoints = 0;

	m_matrix = nullptr;
	m_parentIDs = nullptr;

}

uint32_t MrSkelHandler::GetNumJoints()
{
	return m_numJoints;
}

glm::mat4 * MrSkelHandler::GetMatrix()
{
	return m_matrix;
}

uint32_t * MrSkelHandler::GetParentIDs()
{
	return m_parentIDs;
}
