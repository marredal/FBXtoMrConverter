#ifndef __MRSKELHANDLER_H__
#define __MRSKELHANDLER_H__


#include <fstream>
#include <glm.hpp>


namespace MR
{
	class MrSkelHandler
	{
	public:
		//::.. CONSTURCTORS ..:://
		__declspec(dllexport) MrSkelHandler();
		__declspec(dllexport) virtual ~MrSkelHandler();

		//::.. IMPORT/EXPORT ..:://
		__declspec(dllexport) bool Import(const char * filepath);
		__declspec(dllexport) bool Export(const char * filepath);

		__declspec(dllexport) void Free();

		//::.. GET FUNCTIONS ..:://
		__declspec(dllexport) uint32_t GetNumJoints();
		__declspec(dllexport) glm::mat4 * GetMatrix();
		__declspec(dllexport) uint32_t * GetParentIDs();
		__declspec(dllexport) uint32_t * GetIDs();

		//::.. SET FUNCTIONS ..:://
		__declspec(dllexport) void SetNumJoints(uint32_t numJoints);
		__declspec(dllexport) void SetMatrix(glm::mat4 * mat);
		__declspec(dllexport) void SetParentIDs(uint32_t * parentIDs);
		__declspec(dllexport) void SetIDs(uint32_t * ids);

	private:
		//::.. HELP FUNCTIONS ..:://
		__declspec(dllexport) void Init();

	private:
		bool			m_isLoaded;

		uint32_t		m_numJoints;

		glm::mat4 *		m_matrix;
		uint32_t *		m_parentIDs;
		uint32_t *		m_ids;
	};
}

#endif