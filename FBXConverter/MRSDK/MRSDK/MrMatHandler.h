#ifndef __MRMATHANDLER_H__
#define __MRMATHANDLER_H__


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
	enum MrTextureFlag
	{
		MR_ALBEDO_MAP = 0,
		MR_NORMAL_MAP,
		MR_SGA_MAP
	};



	struct MrTexture
	{
		uint32_t	textureFlag;
		uint32_t	numComponents;
		int32_t		width;
		int32_t		height;
		int32_t *	data;
	};


	class MrMatHandler
	{
	public:
		//::.. CONSTRUCTORS ..:://
		DLL MrMatHandler();
		DLL virtual ~MrMatHandler();

		//::.. IMPORT/EXPORT ..:://
		DLL bool Import(const char * filepath);
		DLL bool Export(const char * filepath);

		DLL void Free();

		//::.. GET FUNCTIONS ..:://
		DLL uint32_t GetNumTextures() const;
		DLL MrTexture * GetTextures() const;

		//::.. SET FUNCTIONS ..:://
		DLL void SetNumTextures(uint32_t numTextures);
		DLL void SetTextures(MrTexture * m_textures);

	private:
		//::.. HELP FUNCTIONS ..:://
		DLL void Init();

	private:
		bool		m_isLoaded;

		uint32_t	m_numTextures;

		MrTexture *	m_textures;
	};
}

#endif