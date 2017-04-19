#ifndef __MRHANDLER_H__
#define __MRHANDLER_H__


#include "MrUtility.h"
#include "MrMeshHandler.h"
#include "MrSkelHandler.h"
#include "MrAnimHandler.h"
#include "MrMatHandler.h"


#include <string>
#include <cstring>
#include <cstdint>


#if DLLEXPORT
#define DLL __declspec(dllexport)
#else
#define DLL __declspec(dllimport)
#endif


namespace mr
{
	class MrHandler
	{
	public:
		//::.. CONSTRUCTORS ..:://
		DLL MrHandler();
		DLL virtual ~MrHandler();

		//::.. IMPORT/EXPORT ..:://
		DLL bool Import(const char * filepath);
		DLL bool Export();

		DLL void Free();

		//::.. GET FUNCTIONS ..:://
		DLL const char * GetName();
		DLL uint32_t GetNumMeshHandlers();
		DLL uint32_t GetNumSkelHandlers();
		DLL uint32_t GetNumAnimHandlers();
		DLL MrMeshHandler * GetMeshHandlers();
		DLL MrSkelHandler * GetSkelHandlers();
		DLL MrAnimHandler * GetAnimHandlers();

		//::.. SET FUNCTIONS ..:://
		DLL void SetName(const char * name);
		DLL void SetMeshHandlers(MrMeshHandler * meshHandlers, uint32_t num);
		DLL void SetSkelHandlers(MrSkelHandler * skelHandlers, uint32_t num);
		DLL void SetAnimHandlers(MrAnimHandler * animHandlers, uint32_t num);

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
