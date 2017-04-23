#pragma once


#include <fstream>
#include <cstdint>
#include <glm.hpp>


#if DLLEXPORT
#define DLL __declspec(dllexport)
#else
#define DLL __declspec(dllimport)
#endif


class MrMeshHandler
{
public:
	  MrMeshHandler();
	  virtual ~MrMeshHandler();

	//::.. IMPORT/EXPORT ..:://
	  bool Import(const char* filepath);
	  bool Export(const char* filepath);

	  void Free();

	//::.. GET FUNCTIONS ..:://
	  const char * GetName();
	  uint32_t	GetNumVerts();
	  glm::vec3 * GetPositions();
	  glm::vec2 * GetTexCoords();
	  glm::vec3 * GetNormals();
	  glm::vec3 * GetTangents();
	  glm::vec3 * GetBiTangents();
	  glm::vec4 * GetSkinWeights();
	  glm::vec4 * GetJointIDs();

	//::.. SET FUNCTIONS ..:://
	  void SetFileName(const char * fileName);
	  void SetNumVerts(uint32_t numVerts);
	  void SetPositions(glm::vec3 * pos);
	  void SetTexCoords(glm::vec2 * tex);
	  void SetNormals(glm::vec3 * nor);
	  void SetTangents(glm::vec3 * tan);
	  void SetBiTangents(glm::vec3 * bi);
	  void SetSkinWeights(glm::vec4 * weights);
	  void SetJointIDs(glm::vec4 * jointIDs);


private:
	//::.. HELP FUNCTIONS .:://
	  void Init();

private:
	bool			m_isLoaded;

	const char *	m_fileName;
	uint32_t		m_numVerts;

	glm::vec3 *		m_postions;
	glm::vec2 *		m_texCoords;
	glm::vec3 *		m_normals;
	glm::vec3 *		m_tangents;
	glm::vec3 *		m_bitangents;
	glm::vec4 *		m_skinWeights;
	glm::vec4 *		m_jointIDs;
};



inline MrMeshHandler::MrMeshHandler()
{
	Init();
}


inline MrMeshHandler::~MrMeshHandler()
{
	Free();
}


inline bool MrMeshHandler::Import(const char * filepath)
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

	float x;
	float y;
	float z;
	float w;

	file.read(reinterpret_cast<char*>(&m_numVerts), sizeof(uint32_t));

	m_postions = new glm::vec3[m_numVerts];
	m_texCoords = new glm::vec2[m_numVerts];
	m_normals = new glm::vec3[m_numVerts];
	m_tangents = new glm::vec3[m_numVerts];
	m_bitangents = new glm::vec3[m_numVerts];
	m_skinWeights = new glm::vec4[m_numVerts];
	m_jointIDs = new glm::vec4[m_numVerts];

	for (uint32_t i = 0; i < m_numVerts; i++)
	{
		// Positions.
		file.read(reinterpret_cast<char*>(&m_postions[i].x), sizeof(float));
		file.read(reinterpret_cast<char*>(&m_postions[i].y), sizeof(float));
		file.read(reinterpret_cast<char*>(&m_postions[i].z), sizeof(float));

		// Texture coords.
		file.read(reinterpret_cast<char*>(&m_texCoords[i].x), sizeof(float));
		file.read(reinterpret_cast<char*>(&m_texCoords[i].y), sizeof(float));

		// Normals.
		file.read(reinterpret_cast<char*>(&m_normals[i].x), sizeof(float));
		file.read(reinterpret_cast<char*>(&m_normals[i].y), sizeof(float));
		file.read(reinterpret_cast<char*>(&m_normals[i].z), sizeof(float));

		// Tangents.
		file.read(reinterpret_cast<char*>(&m_tangents[i].x), sizeof(float));
		file.read(reinterpret_cast<char*>(&m_tangents[i].y), sizeof(float));
		file.read(reinterpret_cast<char*>(&m_tangents[i].z), sizeof(float));

		// Bitangents.
		file.read(reinterpret_cast<char*>(&m_bitangents[i].x), sizeof(float));
		file.read(reinterpret_cast<char*>(&m_bitangents[i].y), sizeof(float));
		file.read(reinterpret_cast<char*>(&m_bitangents[i].z), sizeof(float));

		// Skin weights.
		file.read(reinterpret_cast<char*>(&m_skinWeights[i].x), sizeof(float));
		file.read(reinterpret_cast<char*>(&m_skinWeights[i].y), sizeof(float));
		file.read(reinterpret_cast<char*>(&m_skinWeights[i].z), sizeof(float));
		file.read(reinterpret_cast<char*>(&m_skinWeights[i].w), sizeof(float));

		// Joint weights.
		file.read(reinterpret_cast<char*>(&m_jointIDs[i].x), sizeof(float));
		file.read(reinterpret_cast<char*>(&m_jointIDs[i].y), sizeof(float));
		file.read(reinterpret_cast<char*>(&m_jointIDs[i].z), sizeof(float));
		file.read(reinterpret_cast<char*>(&m_jointIDs[i].w), sizeof(float));
	}

	file.close();

	m_isLoaded = true;

	return true;
}


inline bool MrMeshHandler::Export(const char* filepath)
{
	std::ofstream file(filepath, std::ios::binary);

	if (!file.is_open())
	{
		return false;
	}

	float x;
	float y;
	float z;
	float w;

	file.write(reinterpret_cast<char*>(&m_numVerts), sizeof(uint32_t));

	for (uint32_t i = 0; i < m_numVerts; i++)
	{
		// Positions.
		file.write(reinterpret_cast<char*>(&m_postions[i].x), sizeof(float));
		file.write(reinterpret_cast<char*>(&m_postions[i].y), sizeof(float));
		file.write(reinterpret_cast<char*>(&m_postions[i].z), sizeof(float));


		// Texture coords.
		file.write(reinterpret_cast<char*>(&m_texCoords[i].x), sizeof(float));
		file.write(reinterpret_cast<char*>(&m_texCoords[i].y), sizeof(float));

		// Normals.
		file.write(reinterpret_cast<char*>(&m_normals[i].x), sizeof(float));
		file.write(reinterpret_cast<char*>(&m_normals[i].y), sizeof(float));
		file.write(reinterpret_cast<char*>(&m_normals[i].z), sizeof(float));

		// Tangents.
		file.write(reinterpret_cast<char*>(&m_tangents[i].x), sizeof(float));
		file.write(reinterpret_cast<char*>(&m_tangents[i].y), sizeof(float));
		file.write(reinterpret_cast<char*>(&m_tangents[i].z), sizeof(float));

		// Bitangents.
		file.write(reinterpret_cast<char*>(&m_bitangents[i].x), sizeof(float));
		file.write(reinterpret_cast<char*>(&m_bitangents[i].y), sizeof(float));
		file.write(reinterpret_cast<char*>(&m_bitangents[i].z), sizeof(float));

		// Skin weights.
		file.write(reinterpret_cast<char*>(&m_skinWeights[i].x), sizeof(float));
		file.write(reinterpret_cast<char*>(&m_skinWeights[i].y), sizeof(float));
		file.write(reinterpret_cast<char*>(&m_skinWeights[i].z), sizeof(float));
		file.write(reinterpret_cast<char*>(&m_skinWeights[i].w), sizeof(float));

		// Joint weights.
		file.write(reinterpret_cast<char*>(&m_jointIDs[i].x), sizeof(float));
		file.write(reinterpret_cast<char*>(&m_jointIDs[i].y), sizeof(float));
		file.write(reinterpret_cast<char*>(&m_jointIDs[i].z), sizeof(float));
		file.write(reinterpret_cast<char*>(&m_jointIDs[i].w), sizeof(float));
	}

	file.close();

	return true;
}


inline void MrMeshHandler::Free()
{
	if (!m_isLoaded)
	{
		return;
	}

	delete[] m_postions;
	delete[] m_texCoords;
	delete[] m_normals;
	delete[] m_tangents;
	delete[] m_bitangents;
	delete[] m_skinWeights;
	delete[] m_jointIDs;

	Init();
}


//::.. GET FUNCTIONS ..:://
inline const char * MrMeshHandler::GetName()
{
	return m_fileName;
}


inline uint32_t MrMeshHandler::GetNumVerts()
{
	return m_numVerts;
}


inline glm::vec3 * MrMeshHandler::GetPositions()
{
	return m_postions;
}


inline glm::vec2 * MrMeshHandler::GetTexCoords()
{
	return m_texCoords;
}


inline glm::vec3 * MrMeshHandler::GetNormals()
{
	return m_normals;
}


inline glm::vec3 * MrMeshHandler::GetTangents()
{
	return m_tangents;
}


inline glm::vec3 * MrMeshHandler::GetBiTangents()
{
	return m_bitangents;
}


inline glm::vec4 * MrMeshHandler::GetSkinWeights()
{
	return m_skinWeights;
}


inline glm::vec4 * MrMeshHandler::GetJointIDs()
{
	return m_jointIDs;
}


//::.. SET FUNCTIONS ..:://
inline void MrMeshHandler::SetFileName(const char * fileName)
{
	m_fileName = fileName;
}


inline void MrMeshHandler::SetNumVerts(uint32_t numVerts)
{
	m_numVerts = numVerts;
}


inline void MrMeshHandler::SetPositions(glm::vec3 * pos)
{
	m_postions = pos;
}


inline void MrMeshHandler::SetTexCoords(glm::vec2 * tex)
{
	m_texCoords = tex;
}


inline void MrMeshHandler::SetNormals(glm::vec3 * nor)
{
	m_normals = nor;
}


inline void MrMeshHandler::SetTangents(glm::vec3 * tan)
{
	m_tangents = tan;
}


inline void MrMeshHandler::SetBiTangents(glm::vec3 * bi)
{
	m_bitangents = bi;
}


inline void MrMeshHandler::SetSkinWeights(glm::vec4 * weights)
{
	m_skinWeights = weights;
}


inline void MrMeshHandler::SetJointIDs(glm::vec4 * jointIDs)
{
	m_jointIDs = jointIDs;
}


//::.. HELP FUNCTIONS ..:://
inline void MrMeshHandler::Init()
{
	m_isLoaded = false;

	m_numVerts = 0;

	m_postions = nullptr;
	m_texCoords = nullptr;
	m_normals = nullptr;
	m_tangents = nullptr;
	m_bitangents = nullptr;
	m_skinWeights = nullptr;
	m_jointIDs = nullptr;
}
