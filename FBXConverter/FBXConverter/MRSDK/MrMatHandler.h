#ifndef __MRMATHANDLER_H__
#define __MRMATHANDLER_H__


#include <glm.hpp>


namespace MR
{
	enum MrTextureFlag
	{
		MR_ALBEDO_MAP = 0,
		MR_NORMAL_MAP,
		MR_SPECULAR_GLOW_ALPHA
	};


	struct MrTexture
	{
		uint32_t	numComponents;
		uint32_t	textureFlag;
		int32_t		width;
		int32_t		height;
		float *		data;
	};


	class MrMatHandler
	{
	public:
		//::.. CONSTRUCTORS ..:://
		__declspec(dllexport) MrMatHandler();
		__declspec(dllexport) virtual ~MrMatHandler();

		//::.. IMPORT/EXPORT ..:://
		__declspec(dllexport) bool Import(const char * filepath);
		__declspec(dllexport) bool Export(const char * filepath);

		__declspec(dllexport) void Free();

		//::.. GET FUNCTIONS ..:://
		__declspec(dllexport) uint32_t GetNumTextures() const;
		__declspec(dllexport) MrTexture * GetTextures() const;

		//::.. SET FUNCTIONS ..:://
		__declspec(dllexport) void SetNumTextures(uint32_t numTextures);
		__declspec(dllexport) void SetTextures(MrTexture * m_textures);

	private:
		//::.. HELP FUNCTIONS ..:://
		__declspec(dllexport) void Init();

	private:
		bool		m_isLoaded;

		uint32_t	m_numTextures;

		MrTexture *	m_textures;
	};
}

#endif