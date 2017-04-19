#ifndef __VERTEXINFO_H__
#define __VERTEXINFO_H__


#include "fbxsdk.h"
#include <vector>
#include <iostream>
#include <glm.hpp>


class VertexInfo
{
public:
	VertexInfo();
	virtual ~VertexInfo();

	//..::SAVE FUNCTIONS::..//
	void SavePosition(FbxNode* pNode);
	void SaveUV(FbxNode* pNode);
	void SavetNormal(FbxNode* pNode);
	void SaveTangent(FbxNode* pNode);
	void SaveBiTangent (FbxNode* pNode);

	//..::GET FUNCTIONS::..//
	std::vector<glm::vec3> GetPosition() const;
	std::vector<glm::vec2> GetUV() const;
	std::vector<glm::vec3> GetNormal() const;
	std::vector<glm::vec3> GetTangent() const;
	std::vector<glm::vec3> GetBiTangent() const;


private:

	std::vector <glm::vec3>		m_postion;
	std::vector <glm::vec2>		m_uv;
	std::vector <glm::vec3>		m_normal;
	std::vector <glm::vec3>		m_tangent;
	std::vector <glm::vec3>		m_bitangent;


};

#endif // !__VERTEXINFO_H__