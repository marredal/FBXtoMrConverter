#ifndef __MRMESH_H__
#define __MRMESH_H__


#include <fstream>
#include <cstdint>
#include <glm.hpp>


class MrMeshHandler
{
public:
	MrMeshHandler();
	virtual ~MrMeshHandler();

	bool Import(const char* filepath);

	bool Export(const char* filepath, uint32_t numVerts, 
		glm::vec3 * pos, glm::vec2 * tex, glm::vec3 * nor, 
		glm::vec3 * tan, glm::vec3 * bi, glm::vec4 * weights, 
		glm::vec4 * jointID);


	void Free();

	//::.. GET FUNCTIONS ..:://
	uint32_t	GetNumVerts;
	glm::vec3 * GetPositions();
	glm::vec2 * GetTexCoords();
	glm::vec3 * GetNormals();
	glm::vec3 * GetTangents();
	glm::vec3 * GetBiTangents();
	glm::vec4 * GetSkinWeights();
	glm::vec4 * GetJointIDs();

private:
	bool		m_isLoaded;

	uint64_t	m_numVerts;

	glm::vec3 *	m_postions;
	glm::vec2 *	m_TexCoords;
	glm::vec3 *	m_normals;
	glm::vec3 *	m_tangents;
	glm::vec3 *	m_bitangents;
	glm::vec4 *	m_skinweights;
	glm::vec4 *	m_jointIDs;
};


#endif 