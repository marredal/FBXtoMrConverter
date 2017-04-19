#ifndef __MRANIMHANDLER_H__
#define __MRANIMHANDLER_H__


#include <fstream>
#include <cstdint>
#include <glm.hpp>


#if DLLEXPORT
#define DLL __declspec(dllexport)
#else
#define DLL __declspec(dllimport)
#endif


namespace mr
{
	struct MrKeyFramedJoint
	{
		uint32_t	jointID;
		uint32_t	numKeyframes;
		glm::mat4 *	matrix;
		int32_t	*	keyFrames;
	};


	class MrAnimHandler
	{
	public:
		//::.. CONSTRUCTORS ..:://
		DLL MrAnimHandler();
		DLL virtual ~MrAnimHandler();

		//::.. IMPORT/EXPORT ..:://
		DLL bool Import(const char * filepath);
		DLL bool Export(const char * filepath);

		DLL void Free();

		//::.. SET FUNCTIONS ..:://
		DLL void SetName(const char * name);
		DLL void SetFirstKeyFrame(int32_t firstKeyFrame);
		DLL void SetLastKeyFrame(int32_t lastKeyFrame);
		DLL void SetNumKeyFramedJoints(uint32_t numKeyFramedJoints);
		DLL void SetKeyframedJoint(MrKeyFramedJoint * keyFramedJoints);

		//::.. GET FUNCTIONS ..:://
		DLL const char * GetName();
		DLL int32_t GetFirstKeyFrame();
		DLL int32_t GetLastKeyFrame();
		DLL uint32_t GetNumKeyFramedJoints();
		DLL MrKeyFramedJoint * GetKeyFramedJoints();


	private:
		//::.. HELP FUNCTIONS ..:://
		__declspec(dllexport) void Init();

	private:
		const char *		m_name;

		bool				m_isLoaded;

		int32_t				m_firstKeyFrame;
		int32_t				m_lastKeyFrame;

		uint32_t			m_numKeyFramedJoints;

		MrKeyFramedJoint *	m_keyFramedJoints;

	};
}

#endif // ! __MRANIMHANDLER_H__