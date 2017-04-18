#ifndef __MRANIMHANDLER_H__
#define __MRANIMHANDLER_H__


#include <fstream>
#include <cstdint>
#include <glm.hpp>


struct MrKeyframedJoint
{
	uint32_t	jointID;
	uint32_t	numKeyframes;
	glm::mat4 *	matrix;
	int32_t	*	keyframes;
};


class MrAnimHandler
{
public:
	MrAnimHandler();
	virtual ~MrAnimHandler();

	//::.. IMPORT/EXPORT ..:://
	bool Import(const char * filepath);
	bool Export(const char * filepath, uint32_t numKeyframedJoints,
		MrKeyframedJoint * keyframedJoints);

	//::.. GET FUNCTIONS ..:://
	uint32_t GetNumKeyframedJoints();
	MrKeyframedJoint * GetKeyframedJoint();

	void Free();

private:
	//::.. HELP FUNCTIONS ..:://
	void Init();

private:
	const char *		m_filepath;

	bool				m_isLoaded;

	uint32_t			m_numKeyframedJoints;

	MrKeyframedJoint *	m_keyframedJoints;

};


#endif // ! __MRANIMHANDLER_H__