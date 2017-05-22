#pragma once


#include <fstream>
#include <cstdint>
#include <glm.hpp>


struct MrCamera
{
	glm::vec3	m_position;
	glm::vec3	m_upVector;
	glm::vec3	m_lookAt;
	glm::vec2	m_aspectRatio;
	float		m_FOV;
	float		m_nearPlane;
	float		m_farPlane;
};


class MrCameraHandler
{
public:
	//::.. CONSTRUCTORS ..:://
	MrCameraHandler();
	virtual ~MrCameraHandler();

	//::.. IMPORT/EXPORT ..:://
	bool Import(const char* filepath);
	bool Export(const char* filepath);

	void Free();

	//::.. GET FUNCTIONS ..:://
	uint32_t GetNumCameras();
	MrCamera * GetCameras();

	//::.. SET FUNCTIONS ..:://
	void SetCameras(MrCamera * cameras, uint32_t numCamers);

private:
	//::.. HELP FUNCTIONS .:://
	void Init();

private:
	bool		m_isLoaded;

	uint32_t	m_numCameras;
	MrCamera*	m_cameras;
};


inline MrCameraHandler::MrCameraHandler()
{
	Init();
}


inline MrCameraHandler::~MrCameraHandler()
{
	Free();
}


//::.. EXPORT/IMPORT ..:://
inline bool MrCameraHandler::Import(const char * filepath)
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

	file.read(reinterpret_cast<char*>(&m_numCameras), sizeof(uint32_t));
	m_cameras = new MrCamera[m_numCameras];
	file.read(reinterpret_cast<char*>(m_cameras), sizeof(MrCamera) * m_numCameras);
	
	file.close();

	return true;

}


inline bool MrCameraHandler::Export(const char * filepath)
{
	std::ofstream file(filepath, std::ios::binary);

	if (!file.is_open())
	{
		return false;
	}

	file.write(reinterpret_cast<char*>(&m_cameras), sizeof(MrCamera) * m_numCameras);

	file.close();

	return true;
}


inline void MrCameraHandler::Free()
{
	if (!m_isLoaded)
	{
		return;
	}

	Init();
}


//::.. GET FUNCTIONS ..:://
inline uint32_t MrCameraHandler::GetNumCameras()
{
	return m_numCameras;
}


inline MrCamera * MrCameraHandler::GetCameras()
{
	return m_cameras;
}


//::.. SET FUNCTIONS ..:://
inline void MrCameraHandler::SetCameras(MrCamera * cameras, uint32_t numCamers)
{
	m_numCameras = numCamers;
	m_cameras = cameras;
}


//::.. HELP FUNCTIONS ..:://
inline void MrCameraHandler::Init()
{
	m_cameras = nullptr;
}