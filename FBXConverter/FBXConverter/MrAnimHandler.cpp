#include "MrAnimHandler.h"



MrAnimHandler::MrAnimHandler()
{
	Init();
}


MrAnimHandler::~MrAnimHandler()
{
	Free();
}

bool MrAnimHandler::Import(const char * filepath)
{
	if (m_isLoaded)
	{
		Free();
	}

	std::ifstream file(filepath, std::ios::binary);

	if (!file.is_open)
	{
		return false;
	}

	file.read(reinterpret_cast<char*>(&m_numKeyframedJoints), sizeof(uint32_t));
	file.read(reinterpret_cast<char*>(m_keyframedJoints), sizeof(MrKeyframedJoint) * m_numKeyframedJoints);

	file.close();

	return true;
}

bool MrAnimHandler::Export(const char * filepath, uint32_t numKeyframedJoints,
	MrKeyframedJoint * keyframedJoints)
{
	m_filepath = filepath;

	std::ofstream file(filepath, std::ios::binary);

	if (!file.is_open)
	{
		return false;
	}

	file.write(reinterpret_cast<char*>(&m_numKeyframedJoints), sizeof(uint32_t));
	file.write(reinterpret_cast<char*>(m_keyframedJoints), sizeof(MrKeyframedJoint) * m_numKeyframedJoints);

	file.close();

	return true;
}

uint32_t MrAnimHandler::GetNumKeyframedJoints()
{
	return m_numKeyframedJoints;
}

MrKeyframedJoint * MrAnimHandler::GetKeyframedJoint()
{
	return m_keyframedJoints;
}

void MrAnimHandler::Free()
{
	if (!m_isLoaded)
	{
		return;
	}

	delete[] m_keyframedJoints;

	Init();
}

void MrAnimHandler::Init()
{
	m_isLoaded				= false;

	m_numKeyframedJoints	= 0;

	m_keyframedJoints		= nullptr;
}
