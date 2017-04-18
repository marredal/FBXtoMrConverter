#ifndef __MRSKELHANDLER_H__
#define __MRSKELHANDLER_H__


#include <fstream>
#include <cstdint>
#include <glm.hpp>


class MrSkelHandler
{
public:
	MrSkelHandler();
	virtual ~MrSkelHandler();

	bool Import(const char* filepath);
	bool Export(const char* filepath, uint32_t numJoints, glm::mat4 * mat,
		uint32_t * parentIDs);

	void Free();

	//::.. GET FUNCTIONS ..:://
	uint32_t GetNumJoints();
	glm::mat4 * GetMatrix();
	uint32_t * GetParentIDs();

private:
	bool m_isLoaded;

	uint32_t m_numJoints;

	glm::mat4 * m_matrix;
	uint32_t *	m_parentIDs;

};



#endif