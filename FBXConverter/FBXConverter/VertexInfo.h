#ifndef __VERTEXINFO_H__
#define __VERTEXINFO_H__


#include "Manager.h"


class VertexInfo
{
public:
	VertexInfo();
	virtual ~VertexInfo();

	void SetInfo(FbxMesh &mesh);

	void SetPosition(FbxMesh *mesh);
	void SetUV(FbxMesh *mesh);
	void SetNormal(FbxMesh &mesh);
	void SetTangent(FbxMesh) &mesh);
	void SetBiTangent (FbxMEsh &mesh);

	//..::GET FUNCTIONS::..//
	void GetPosition() const;
	void GetUV() const;
	void GetNormal() const;
	void GetTangent() const;
	void GetBiTangent() const;


private:

	std::vector <Vec3>					m_postion;
	std::vector <FbxVector2>			m_uv;
	std::vector <Vec3>					m_normal;
	std::vector <Vec3>					m_tangent;
	std::vector <Vec3>					m_bitangent;


};

#endif // !__VERTEXINFO_H__