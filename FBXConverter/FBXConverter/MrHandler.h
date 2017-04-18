#ifndef __MRHANDLER_H__
#define __MRHANDLER_H__


#include "MrMeshHandler.h"
#include "MrSkelHandler.h"
#include "MrAnimHandler.h"


#include <cstdint>


class MrHandler
{
public:
	MrHandler();
	virtual ~MrHandler();

	//::.. IMPORT/EXPORT ..:://
	bool Import(const char * filepath);
	bool Export(const char * filepath, MrMeshHandler mesh,
		MrSkelHandler skel, uint32_t numAnimations,
		MrAnimHandler * anim);

	//::.. GET FUNCTIONS ..:://
	uint32_t GetNumAnimations();

private:
	


	uint32_t	m_numAnimations;

};


#endif // !__MRHANDLER_H__
