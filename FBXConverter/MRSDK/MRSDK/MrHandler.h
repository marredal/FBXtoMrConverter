#ifndef __MRHANDLER_H__
#define __MRHANDLER_H__


#include "MrUtility.h"
#include "MrMeshHandler.h"
#include "MrSkelHandler.h"
#include "MrAnimHandler.h"

#include <string>
#include <cstring>
#include <cstdint>

namespace MR
{
	class MrHandler
	{
	public:
		//::.. CONSTRUCTORS ..:://
		__declspec(dllexport) MrHandler();
		__declspec(dllexport) virtual ~MrHandler();

		//::.. IMPORT/EXPORT ..:://
		__declspec(dllexport) bool Import(const char * filepath);
		__declspec(dllexport) bool Export();

		__declspec(dllexport) void Free();

		//::.. GET FUNCTIONS ..:://
		__declspec(dllexport) const char * GetName();
		__declspec(dllexport) uint32_t GetNumMeshHandlers();
		__declspec(dllexport) uint32_t GetNumSkelHandlers();
		__declspec(dllexport) uint32_t GetNumAnimHandlers();
		__declspec(dllexport) MrMeshHandler * GetMeshHandlers();
		__declspec(dllexport) MrSkelHandler * GetSkelHandlers();
		__declspec(dllexport) MrAnimHandler * GetAnimHandlers();

		//::.. SET FUNCTIONS ..:://
		__declspec(dllexport) void SetName(const char * name);
		__declspec(dllexport) void SetMeshHandlers(MrMeshHandler * meshHandlers, uint32_t num);
		__declspec(dllexport) void SetSkelHandlers(MrSkelHandler * skelHandlers, uint32_t num);
		__declspec(dllexport) void SetAnimHandlers(MrAnimHandler * animHandlers, uint32_t num);

	private:
		//::.. HELP FUNCTIONS ..:://
		__declspec(dllexport) void Init();

	private:
		bool			m_isLoaded;

		const char *	m_name;

		uint32_t		m_numMeshHandlers;
		uint32_t		m_numSkelHandlers;
		uint32_t		m_numAnimHandlers;

		MrMeshHandler * m_meshHandler;
		MrSkelHandler * m_skelHandler;
		MrAnimHandler * m_animHandler;
	};
}

#endif // !__MRHANDLER_H__
