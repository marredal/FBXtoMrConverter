#ifndef __MRMESH_H__
#define __MRMESH_H__


#include <fstream>
#include <cstdint>
#include <glm.hpp>

namespace MR
{
	class MrMeshHandler
	{
	public:
		__declspec(dllexport) MrMeshHandler();
		__declspec(dllexport) virtual ~MrMeshHandler();

		//::.. IMPORT/EXPORT ..:://
		__declspec(dllexport) bool Import(const char* filepath);
		__declspec(dllexport) bool Export(const char* filepath);

		void Free();

		//::.. GET FUNCTIONS ..:://
		__declspec(dllexport) const char * GetName();
		__declspec(dllexport) uint32_t	GetNumVerts();
		__declspec(dllexport) glm::vec3 * GetPositions();
		__declspec(dllexport) glm::vec2 * GetTexCoords();
		__declspec(dllexport) glm::vec3 * GetNormals();
		__declspec(dllexport) glm::vec3 * GetTangents();
		__declspec(dllexport) glm::vec3 * GetBiTangents();
		__declspec(dllexport) glm::vec4 * GetSkinWeights();
		__declspec(dllexport) glm::vec4 * GetJointIDs();

		//::.. SET FUNCTIONS ..:://
		__declspec(dllexport) void SetFileName(const char * fileName);
		__declspec(dllexport) void SetNumVerts(uint32_t numVerts);
		__declspec(dllexport) void SetPositions(glm::vec3 * pos);
		__declspec(dllexport) void SetTexCoords(glm::vec2 * tex);
		__declspec(dllexport) void SetNormals(glm::vec3 * nor);
		__declspec(dllexport) void SetTangents(glm::vec3 * tan);
		__declspec(dllexport) void SetBiTangents(glm::vec3 * bi);
		__declspec(dllexport) void SetSkinWeights(glm::vec4 * weights);
		__declspec(dllexport) void SetJointIDs(glm::vec4 * jointIDs);


	private:
		//::.. HELP FUNCTIONS .:://
		__declspec(dllexport) void Init();

	private:
		bool			m_isLoaded;

		const char *	m_fileName;
		uint64_t		m_numVerts;

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