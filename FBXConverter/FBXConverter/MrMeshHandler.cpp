#include "MrMeshHandler.h"



MrMeshHandler::MrMeshHandler()
{
	Init();
}


MrMeshHandler::~MrMeshHandler()
{
	Free();
}


bool MrMeshHandler::Import(const char * filepath)
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

	file.read(reinterpret_cast<char*>(&m_numVerts), sizeof(uint32_t));
	file.read(reinterpret_cast<char*>(m_postions), sizeof(glm::vec3) * m_numVerts);
	file.read(reinterpret_cast<char*>(m_TexCoords), sizeof(glm::vec2) * m_numVerts);
	file.read(reinterpret_cast<char*>(m_normals), sizeof(glm::vec3) * m_numVerts);
	file.read(reinterpret_cast<char*>(m_tangents), sizeof(glm::vec3) * m_numVerts);
	file.read(reinterpret_cast<char*>(m_bitangents), sizeof(glm::vec3) * m_numVerts);
	file.read(reinterpret_cast<char*>(m_skinweights), sizeof(glm::vec4) * m_numVerts);
	file.read(reinterpret_cast<char*>(m_jointIDs), sizeof(glm::vec4) * m_numVerts);

	file.close();

	return true;
}


bool MrMeshHandler::Export(const char* filepath, uint32_t numVerts,
	glm::vec3 * pos, glm::vec2 * tex, glm::vec3 * nor,
	glm::vec3 * tan, glm::vec3 * bi, glm::vec4 * weights,
	glm::vec4 * jointID)
{
	std::ofstream file(filepath, std::ios::binary);

	if (!file.is_open())
	{
		return false;
	}

	file.write(reinterpret_cast<char*>(&numVerts), sizeof(uint32_t));
	file.write(reinterpret_cast<char*>(pos), sizeof(glm::vec3) * numVerts);
	file.write(reinterpret_cast<char*>(tex), sizeof(glm::vec2) * numVerts);
	file.write(reinterpret_cast<char*>(nor), sizeof(glm::vec3) * numVerts);
	file.write(reinterpret_cast<char*>(tan), sizeof(glm::vec3) * numVerts);
	file.write(reinterpret_cast<char*>(bi), sizeof(glm::vec3) * numVerts);
	file.write(reinterpret_cast<char*>(weights), sizeof(glm::vec4) * numVerts);
	file.write(reinterpret_cast<char*>(jointID), sizeof(glm::vec4) * numVerts);

	file.close();

	m_isLoaded = true;
	return true;
}


void MrMeshHandler::Free()
{
	if (!m_isLoaded)
	{
		return;
	}

	delete[] m_postions;
	delete[] m_TexCoords;
	delete[] m_normals;
	delete[] m_tangents;
	delete[] m_bitangents;
	delete[] m_skinweights;
	delete[] m_jointIDs;

	Init();
}


//::.. GET FUNCTIONS ..:://
glm::vec3 * MrMeshHandler::GetPositions()
{
	return m_postions;
}


glm::vec2 * MrMeshHandler::GetTexCoords()
{
	return m_TexCoords;
}


glm::vec3 * MrMeshHandler::GetNormals()
{
	return m_normals;
}


glm::vec3 * MrMeshHandler::GetTangents()
{
	return m_tangents;
}


glm::vec3 * MrMeshHandler::GetBiTangents()
{
	return m_bitangents;
}


glm::vec4 * MrMeshHandler::GetSkinWeights()
{
	return m_skinweights;
}

glm::vec4 * MrMeshHandler::GetJointIDs()
{
	return m_jointIDs;
}

void MrMeshHandler::Init()
{
	m_isLoaded = false;

	m_numVerts = 0;

	m_postions = nullptr;
	m_TexCoords = nullptr;
	m_normals = nullptr;
	m_tangents = nullptr;
	m_bitangents = nullptr;
	m_skinweights = nullptr;
	m_jointIDs = nullptr;
}
