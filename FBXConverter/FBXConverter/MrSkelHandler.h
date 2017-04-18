#ifndef __MRSKELHANDLER_H__
#define __MRSKELHANDLER_H__


#include <fstream>
#include <glm.hpp>


class MrSkelHandler
{
public:
	MrSkelHandler();
	virtual ~MrSkelHandler();

	//::.. IMPORT/EXPORT ..:://
	bool Import(const char* filepath);
	bool Export();
	bool Export(const char* filepath, uint32_t numJoints, glm::mat4 * mat, 
		uint32_t * IDs, uint32_t * parentIDs);

	void Free();

	//::.. GET FUNCTIONS ..:://
	uint32_t GetNumJoints();
	glm::mat4 * GetMatrix();
	uint32_t * GetParentIDs();
	uint32_t * GetIDs();

	//::.. SET FUNCTIONS ..:://
	void SetNumJoints(uint32_t numJoints);
	void SetMatrix(glm::mat4 * mat);
	void SetParentIDs(uint32_t * parentIDs);
	void SetIDs(uint32_t * ids);

private:
	//::.. HELP FUNCTIONS ..:://
	void Init();

private:
	bool m_isLoaded;

	uint32_t m_numJoints;

	glm::mat4 * m_matrix;
	uint32_t *	m_parentIDs;
	uint32_t *	m_ids;
};


#endif