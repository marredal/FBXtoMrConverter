#pragma once


#include <fstream>
#include <cstdint>
#include <glm.hpp>


#if DLLEXPORT
#define DLL __declspec(dllexport)
#else
#define DLL __declspec(dllimport)
#endif

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
	glm::vec3 GetPosition();
	glm::vec3 GetUpVector();
	glm::vec3 GetLookAt();
	glm::vec2 GetAspectRatio();
	float GetFOV();
	float GetNearPlane();
	float GetFarPlane();
	bool GetIsLoaded();
	const char * GetFileName();

	//::.. SET FUNCTIONS ..:://
	glm::vec3 SetPosition(glm::vec3 value);
	glm::vec3 SetUpVector(glm::vec3 value);
	glm::vec3 SetLookAt(glm::vec3 value);
	glm::vec2 SetAspectRatio(glm::vec2 value);
	float SetFOV(float value);
	float SetNearPlane(float value);
	float SetFarPlane(float value);


private:
	//::.. HELP FUNCTIONS .:://
	void Init();

private:

	struct MrCameraOptions
	{
		glm::vec3	m_position;
		glm::vec3	m_upVector;
		glm::vec3	m_lookAt;
		glm::vec2	m_aspectRatio;
		float		m_FOV;
		float		m_nearPlane;
		float		m_farPlane;
		bool		m_isLoaded;
	};

	const char *	m_fileName;

	MrCameraOptions	m_camera;

};


inline MrCameraHandler::MrCameraHandler()
{
	Init();
}

inline MrCameraHandler::~MrCameraHandler()
{
	Free();
}

inline void MrCameraHandler::Init()
{
	m_camera.m_position = glm::vec3(0);
	m_camera.m_upVector = glm::vec3(0);
	m_camera.m_lookAt = glm::vec3(0);
	m_camera.m_aspectRatio = glm::vec2(0);
	m_camera.m_FOV = 0;
	m_camera.m_nearPlane = 0;
	m_camera.m_farPlane = 0;
	m_camera.m_isLoaded = false;
	m_fileName = "UNKNOWN";
}

inline bool MrCameraHandler::Import(const char * filepath)
{
	if (m_camera.m_isLoaded)
	{
		Free();
	}

	std::ifstream file(filepath, std::ios::binary);

	if (!file.is_open())
	{
		return false;
	}

	file.read(reinterpret_cast<char*>(&m_camera), sizeof(MrCameraOptions));
	
	file.close();
	m_camera.m_isLoaded = true;

	return true;

}

inline bool MrCameraHandler::Export(const char * filepath)
{
	std::ofstream file(filepath, std::ios::binary);

	if (!file.is_open())
	{
		return false;
	}

	file.write(reinterpret_cast<char*>(&m_camera), sizeof(MrCameraOptions));

	file.close();

	return true;
}

inline void MrCameraHandler::Free()
{
	if (!m_camera.m_isLoaded)
	{
		return;
	}

	Init();
}

inline glm::vec3 MrCameraHandler::GetPosition()
{
	return m_camera.m_position;
}


inline glm::vec3 MrCameraHandler::GetUpVector()
{
	return m_camera.m_upVector;
}

inline glm::vec3 MrCameraHandler::GetLookAt()
{
	return m_camera.m_lookAt;
}

inline glm::vec2 MrCameraHandler::GetAspectRatio()
{
	return m_camera.m_aspectRatio;
}

inline float MrCameraHandler::GetFOV()
{
	return m_camera.m_FOV;
}

inline float MrCameraHandler::GetNearPlane()
{
	return m_camera.m_nearPlane;
}

inline float MrCameraHandler::GetFarPlane()
{
	return m_camera.m_farPlane;
}

inline bool MrCameraHandler::GetIsLoaded()
{
	return m_camera.m_isLoaded;
}

inline const char * MrCameraHandler::GetFileName()
{
	return m_fileName;
}

inline glm::vec3 MrCameraHandler::SetPosition(glm::vec3 value)
{
	m_camera.m_position = value;
}

inline glm::vec3 MrCameraHandler::SetUpVector(glm::vec3 value)
{
	m_camera.m_upVector = value;
}

inline glm::vec3 MrCameraHandler::SetLookAt(glm::vec3 value)
{
	m_camera.m_lookAt = value;
}

inline glm::vec2 MrCameraHandler::SetAspectRatio(glm::vec2 value)
{
	m_camera.m_aspectRatio = value;
}

inline float MrCameraHandler::SetFOV(float value)
{
	m_camera.m_FOV = value;
}

inline float MrCameraHandler::SetNearPlane(float value)
{
	m_camera.m_nearPlane = value;
}

inline float MrCameraHandler::SetFarPlane(float value)
{
	m_camera.m_farPlane = value;
}