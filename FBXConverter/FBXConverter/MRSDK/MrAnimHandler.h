#ifndef __MRANIMHANDLER_H__
#define __MRANIMHANDLER_H__


#include <fstream>
#include <cstdint>
#include <glm.hpp>


namespace MR
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
		__declspec(dllexport) MrAnimHandler();
		__declspec(dllexport) virtual ~MrAnimHandler();

		//::.. IMPORT/EXPORT ..:://
		__declspec(dllexport) bool Import(const char * filepath);
		__declspec(dllexport) bool Export(const char * filepath);

		__declspec(dllexport) void Free();

		//::.. SET FUNCTIONS ..:://
		__declspec(dllexport) void SetName(const char * name);
		__declspec(dllexport) void SetFirstKeyFrame(int32_t firstKeyFrame);
		__declspec(dllexport) void SetLastKeyFrame(int32_t lastKeyFrame);
		__declspec(dllexport) void SetNumKeyFramedJoints(uint32_t numKeyFramedJoints);
		__declspec(dllexport) void SetKeyframedJoint(MrKeyFramedJoint * keyFramedJoints);

		//::.. GET FUNCTIONS ..:://
		__declspec(dllexport) const char * GetName();
		__declspec(dllexport) int32_t GetFirstKeyFrame();
		__declspec(dllexport) int32_t GetLastKeyFrame();
		__declspec(dllexport) uint32_t GetNumKeyFramedJoints();
		__declspec(dllexport) MrKeyFramedJoint * GetKeyFramedJoints();


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