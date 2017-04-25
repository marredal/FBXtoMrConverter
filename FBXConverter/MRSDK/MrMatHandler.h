#pragma once


#include <fstream>
#include <cstdint>
#include <glm.hpp>


struct MrTexture
{
	uint32_t	width;
	uint32_t	height;
	uint32_t	numComponents;
	uint8_t	*	data;
};

class MrMatHandler
{
public:
	//::.. CONSTRUCTORS ..:://
	MrMatHandler();
	virtual ~MrMatHandler();

	//::.. IMPORT/EXPORT ..:://
	bool Import(const char* filepath);
	bool Export(const char* filepath);

	void Free();

private:
	//::.. HELP FUNCTIONS ..:://

private:
	MrTexture * m_normalMap;


};

inline MrMatHandler::MrMatHandler()
{

}

inline MrMatHandler::~MrMatHandler()
{
}


//::.. IMPORT/EXPORT ..:://
inline bool MrMatHandler::Import(const char * filepath)
{
	return false;
}


inline bool MrMatHandler::Export(const char * filepath)
{
	return false;
}


inline void MrMatHandler::Free()
{
}
