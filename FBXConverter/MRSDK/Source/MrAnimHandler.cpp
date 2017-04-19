#include "MrAnimHandler.h"


namespace MR
{
	//::.. CONSTRUCTORS ..:://
	MrAnimHandler::MrAnimHandler()
	{
		Init();
	}


	MrAnimHandler::~MrAnimHandler()
	{
		Free();
	}


	//::.. IMPORT/EXPORT ..:://
	bool MrAnimHandler::Import(const char * filepath)
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

		file.read(reinterpret_cast<char*>(&m_numKeyFramedJoints), sizeof(uint32_t));

		m_keyFramedJoints = new MrKeyFramedJoint[m_numKeyFramedJoints];

		for (uint32_t i = 0; i < m_numKeyFramedJoints; i++)
		{
			file.read(reinterpret_cast<char*>(&m_keyFramedJoints[i].jointID), sizeof(uint32_t));
			file.read(reinterpret_cast<char*>(&m_keyFramedJoints[i].numKeyframes), sizeof(uint32_t));

			m_keyFramedJoints[i].matrix = new glm::mat4[m_numKeyFramedJoints];
			m_keyFramedJoints[i].keyFrames = new int32_t[m_numKeyFramedJoints];

			file.read(reinterpret_cast<char*>(m_keyFramedJoints[i].matrix), sizeof(glm::mat4) * m_keyFramedJoints[i].numKeyframes);
			file.read(reinterpret_cast<char*>(m_keyFramedJoints[i].keyFrames), sizeof(int32_t) * m_keyFramedJoints[i].numKeyframes);
		}

		file.close();

		return true;
	}


	bool MrAnimHandler::Export(const char * filepath)
	{
		std::ofstream file(filepath, std::ios::binary);

		if (!file.is_open())
		{
			return false;
		}

		file.write(reinterpret_cast<char*>(&m_numKeyFramedJoints), sizeof(uint32_t));

		for (uint32_t i = 0; i < m_numKeyFramedJoints; i++)
		{
			file.write(reinterpret_cast<char*>(&m_keyFramedJoints[i].jointID), sizeof(uint32_t));
			file.write(reinterpret_cast<char*>(&m_keyFramedJoints[i].numKeyframes), sizeof(uint32_t));
			file.write(reinterpret_cast<char*>(m_keyFramedJoints[i].matrix), sizeof(glm::mat4) * m_keyFramedJoints[i].numKeyframes);
			file.write(reinterpret_cast<char*>(m_keyFramedJoints[i].keyFrames), sizeof(int32_t) * m_keyFramedJoints[i].numKeyframes);
		}

		file.close();

		return true;
	}


	void MrAnimHandler::Free()
	{
		if (!m_isLoaded)
		{
			return;
		}

		for (uint32_t i = 0; i < m_numKeyFramedJoints; i++)
		{
			delete[] m_keyFramedJoints[i].matrix;
			delete[] m_keyFramedJoints[i].keyFrames;
		}

		delete[] m_keyFramedJoints;

		Init();
	}


	//::.. SET FUNCTIONS ..:://
	void MrAnimHandler::SetName(const char * name)
	{
		m_name = name;
		m_isLoaded = true;
	}


	void MrAnimHandler::SetFirstKeyFrame(int32_t firstKeyFrame)
	{
		m_firstKeyFrame = firstKeyFrame;
		m_isLoaded = true;
	}


	void MrAnimHandler::SetLastKeyFrame(int32_t lastKeyFrame)
	{
		m_lastKeyFrame = lastKeyFrame;
		m_isLoaded = true;
	}


	void MrAnimHandler::SetNumKeyFramedJoints(uint32_t numKeyFramedJoints)
	{
		m_numKeyFramedJoints = numKeyFramedJoints;
		m_isLoaded = true;
	}


	void MrAnimHandler::SetKeyframedJoint(MrKeyFramedJoint * keyFramedJoints)
	{
		m_keyFramedJoints = keyFramedJoints;
	}


	//::.. GET FUNCTIONS ..:://
	const char * MrAnimHandler::GetName()
	{
		return m_name;
	}


	int32_t MrAnimHandler::GetFirstKeyFrame()
	{
		return m_firstKeyFrame;
	}


	int32_t MrAnimHandler::GetLastKeyFrame()
	{
		return m_lastKeyFrame;
	}


	uint32_t MrAnimHandler::GetNumKeyFramedJoints()
	{
		return m_numKeyFramedJoints;
	}


	MrKeyFramedJoint * MrAnimHandler::GetKeyFramedJoints()
	{
		return m_keyFramedJoints;
	}


	//::.. HELP FUNCTIONS ..:://
	void MrAnimHandler::Init()
	{
		m_isLoaded = false;

		m_numKeyFramedJoints = 0;

		m_keyFramedJoints = nullptr;
	}
}