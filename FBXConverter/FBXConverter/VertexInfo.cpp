#include "VertexInfo.h"



VertexInfo::VertexInfo()
{


}


VertexInfo::~VertexInfo()
{
}


void VertexInfo::SetInfo(FbxMesh &mesh)
{
	if (mesh)
	{



	}
}

void VertexInfo::SetPosition(FbxMesh *mesh)
{
	Vec3 temp;

	for (int i = 0; i < mesh->GetControlPointsCount(); i++)
	{
		temp.x = mesh->GetControlPointAt(i).mData[0];
		temp.x = mesh->GetControlPointAt(i).mData[1];
		temp.z = mesh->GetControlPointAt(i).mData[2];
		m_postion.push_back(temp);
	}
}

void VertexInfo::SetUV(FbxMesh *mesh)
{

	FbxStringList uvSetNameList;
	mesh->GetUVSetNames(uvSetNameList);
	for (int index = 0; index < uvSetNameList.GetCount(); index++)
	{
		const char* uvSetName = uvSetNameList.GetStringAt(index);
		const FbxGeometryElementUV* uvElement = mesh->GetElementUV(uvSetName);

		if (!uvElement)
		{
			continue;
		}

		if (uvElement->GetMappingMode() != FbxGeometryElement::eByPolygonVertex && 
			uvElement->GetMappingMode() != FbxGeometryElement::eByControlPoint)
		{
			return;
		}

		const bool UseIndex = uvElement->GetReferenceMode() != FbxGeometryElement::eDirect;
		const int indexCount = (UseIndex) ? uvElement->GetIndexArray().GetCount() : 0;

		const int polyCount = mesh->GetPolygonCount();

		if (uvElement->GetMappingMode() == FbxGeometryElement::eByControlPoint)
		{
			int vertexCounter = 0;
			for (int polyIndex = 0; polyIndex < polyCount; polyIndex++)
			{
				const int polySize = mesh->GetPolygonSize(polyIndex);
				for (int i = 0; i < polySize; i++)
				{

				}
			}
		}
	}


}
