#include "MrHandler.h"



MrHandler::MrHandler()
{
}


MrHandler::~MrHandler()
{
}


//::.. IMPORT/EXPORT ..:://
bool MrHandler::Import(const char * filepath)
{
	return false;
}

bool MrHandler::Export(const char * filepath, MrMeshHandler mesh, 
	MrSkelHandler skel, uint32_t numAnimations, MrAnimHandler * anim)
{


	return false;
}

uint32_t MrHandler::GetNumAnimations()
{
	return uint32_t();
}

