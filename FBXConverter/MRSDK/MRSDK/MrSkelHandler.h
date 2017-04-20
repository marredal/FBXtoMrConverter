#ifndef __MRSKELHANDLER_H__
#define __MRSKELHANDLER_H__

#include <MrUtility.h>
#include <fstream>
#include <glm.hpp>


#if DLLEXPORT
#define DLL __declspec(dllexport)
#else
#define DLL __declspec(dllimport)
#endif


namespace mr
{
	class MrSkelHandler
	{
	public:
		//::.. CONSTURCTORS ..:://
		DLL MrSkelHandler();
		DLL virtual ~MrSkelHandler();

		//::.. IMPORT/EXPORT ..:://
		DLL bool Import(const char * filepath);
		DLL bool Export(const char * filepath);

		DLL void Free();

		//::.. GET FUNCTIONS ..:://
		DLL uint32_t GetNumJoints();
		DLL glm::mat4 * GetMatrix();
		DLL uint32_t * GetParentIDs();
		DLL uint32_t * GetIDs();

		//::.. SET FUNCTIONS ..:://
		DLL void SetNumJoints(uint32_t numJoints);
		DLL void SetMatrix(glm::mat4 * mat);
		DLL void SetParentIDs(uint32_t * parentIDs);
		DLL void SetIDs(uint32_t * ids);

	private:
		//::.. HELP FUNCTIONS ..:://
		DLL void Init();

	private:
		bool			m_isLoaded;

		uint32_t		m_numJoints;

		glm::mat4 *		m_matrix;
		uint32_t *		m_parentIDs;
		uint32_t *		m_ids;
	};
}

#endif