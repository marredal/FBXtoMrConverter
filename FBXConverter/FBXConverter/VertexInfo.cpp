#include "VertexInfo.h"



VertexInfo::VertexInfo()
{


}


VertexInfo::~VertexInfo()
{
}



void VertexInfo::SetPosition(FbxNode* pNode)
{
	if (!pNode)
		return;

	//get mesh
	FbxMesh* mesh = pNode->GetMesh();
	if (mesh)
	{

		glm::vec3 output;

		for (int i = 0; i < mesh->GetControlPointsCount(); i++)
		{
			output.x = mesh->GetControlPointAt(i).mData[0];
			output.x = mesh->GetControlPointAt(i).mData[1];
			output.z = mesh->GetControlPointAt(i).mData[2];
			m_postion.push_back(output);
		}
	}
}

void VertexInfo::SetUV(FbxNode* pNode)
{

	if (!pNode)
		return;

	//get mesh
	FbxMesh* mesh = pNode->GetMesh();
	if (mesh)
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
						FbxVector2 UVvalue;
						int polyVertIndex = mesh->GetPolygonSize(polyIndex);

						int uvIndex = UseIndex ? uvElement->GetIndexArray().GetAt(polyVertIndex) : polyVertIndex;
						UVvalue = uvElement->GetDirectArray().GetAt(uvIndex);
						vertexCounter++;
						//kanske inte funkar
						m_uv.push_back(glm::vec2((float)UVvalue[0], (float)UVvalue[1]));

					}
				}
			}
			else if (uvElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
			{
				int vertexCounter = 0;
				for (int polyIndex = 0; polyIndex < polyCount; polyIndex++)
				{
					const int polySize = mesh->GetPolygonSize(polyIndex);
					for (int i = 0; i < polySize; i++)
					{
						if (vertexCounter < indexCount)
						{
							FbxVector2 uvValue;

							int uvIndex = UseIndex ? uvElement->GetIndexArray().GetAt(vertexCounter) : vertexCounter;

							uvValue = uvElement->GetDirectArray().GetAt(uvIndex);
							vertexCounter++;
							m_uv.push_back(glm::vec2((float)uvValue[0], (float)uvValue[1]));

						}
					}
				}
			}
		}
	}
	int count = pNode->GetChildCount();
	for (int i = 0; i < count; i++)
	{
		this->SetUV(pNode->GetChild(i));
	}
}


