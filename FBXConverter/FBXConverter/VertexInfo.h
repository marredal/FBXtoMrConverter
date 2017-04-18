#ifndef __VERTEXINFO_H__
#define __VERTEXINFO_H__


#include "Manager.h"
#include <glm.hpp>


class VertexInfo
{
public:
	VertexInfo();
	virtual ~VertexInfo();

	void SetInfo(FbxMesh &mesh);

	void SetPosition(FbxNode* pNode);
	void SetUV(FbxNode* pNode);
	void SetNormal(FbxNode* pNode);
	void SetTangent(FbxNode* pNode);
	void SetBiTangent (FbxNode* pNode);

	//..::GET FUNCTIONS::..//
	void GetPosition() const;
	void GetUV() const;
	void GetNormal() const;
	void GetTangent() const;
	void GetBiTangent() const;


private:

	std::vector <glm::vec3>					m_postion;
	std::vector <glm::vec2>					m_uv;
	std::vector <glm::vec3>					m_normal;
	std::vector <glm::vec3>					m_tangent;
	std::vector <glm::vec3>					m_bitangent;


};

#endif // !__VERTEXINFO_H__