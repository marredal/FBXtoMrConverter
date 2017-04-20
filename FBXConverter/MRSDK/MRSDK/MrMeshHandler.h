#ifndef __MRMESH_H__
#define __MRMESH_H__


#include <fstream>
#include <cstdint>
#include <glm.hpp>


#if DLLEXPORT
#define DLL __declspec(dllexport)
#else
#define DLL __declspec(dllimport)
#endif


namespace mr
{
	class MrMeshHandler
	{
	public:
		DLL MrMeshHandler();
		DLL virtual ~MrMeshHandler();

		//::.. IMPORT/EXPORT ..:://
		DLL bool Import(const char* filepath);
		DLL bool Export(const char* filepath);

		DLL void Free();

		//::.. GET FUNCTIONS ..:://
		DLL const char * GetName();
		DLL uint32_t	GetNumVerts();
		DLL glm::vec3 * GetPositions();
		DLL glm::vec2 * GetTexCoords();
		DLL glm::vec3 * GetNormals();
		DLL glm::vec3 * GetTangents();
		DLL glm::vec3 * GetBiTangents();
		DLL glm::vec4 * GetSkinWeights();
		DLL glm::vec4 * GetJointIDs();

		//::.. SET FUNCTIONS ..:://
		DLL void SetFileName(const char * fileName);
		DLL void SetNumVerts(uint32_t numVerts);
		DLL void SetPositions(glm::vec3 * pos);
		DLL void SetTexCoords(glm::vec2 * tex);
		DLL void SetNormals(glm::vec3 * nor);
		DLL void SetTangents(glm::vec3 * tan);
		DLL void SetBiTangents(glm::vec3 * bi);
		DLL void SetSkinWeights(glm::vec4 * weights);
		DLL void SetJointIDs(glm::vec4 * jointIDs);


	private:
		//::.. HELP FUNCTIONS .:://
		DLL void Init();

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
}

#endif 