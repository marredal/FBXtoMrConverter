#include "VertexInfo.h"



VertexInfo::VertexInfo()
{


}


VertexInfo::~VertexInfo()
{
}

void VertexInfo::init()
{

}



void VertexInfo::SavePosition(FbxNode* pNode)
{
	if (!pNode)
		return;

	//get mesh
	FbxMesh* mesh = pNode->GetMesh();
	if (mesh)
	{
		for (int i = 0; i < mesh->GetControlPointsCount(); i++)
		{
			glm::vec3 output;
			output.x = mesh->GetControlPointAt(i).mData[0];
			output.y = mesh->GetControlPointAt(i).mData[1];
			output.z = mesh->GetControlPointAt(i).mData[2];
			m_postion.push_back(output);
		}
	}
	/*int count = pNode->GetChildCount();
	for (int i = 0; i < count; i++)
	{
		SavePosition(pNode->GetChild(i));
	}*/
}

void VertexInfo::SaveUV(FbxNode* pNode)
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
						FbxVector2 output;
						int polyVertIndex = mesh->GetPolygonSize(polyIndex);

						int uvIndex = UseIndex ? uvElement->GetIndexArray().GetAt(polyVertIndex) : polyVertIndex;
						output = uvElement->GetDirectArray().GetAt(uvIndex);
						vertexCounter++;
						//kanske inte funkar
						m_uv.push_back(glm::vec2((float)output[0], (float)output[1]));

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
		this->SaveUV(pNode->GetChild(i));
	}
}

void VertexInfo::SavetNormal(FbxNode * pNode)
{
	if (!pNode)
		return;

	FbxMesh* mesh = pNode->GetMesh();
	if (mesh)
	{
		FbxGeometryElementNormal* normalElement = mesh->GetElementNormal();

		if (normalElement)
		{
			if (normalElement->GetMappingMode() == FbxGeometryElement::eByControlPoint)
			{

				for (int vertexIndex = 0; vertexIndex < mesh->GetControlPointsCount(); vertexIndex++)
				{
					int normalIndex = 0;

					if (normalElement->GetReferenceMode() == FbxGeometryElement::eDirect)
						normalIndex = vertexIndex;

					if (normalElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
						normalIndex = normalElement->GetIndexArray().GetAt(vertexIndex);

					FbxDouble3 normal = normalElement->GetDirectArray().GetAt(normalIndex);

					m_normal.push_back(glm::vec3(normal[0], normal[1], normal[2]));
				}
			}
			else if(normalElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
			{
				int indexByPolygonVertex = 0;

				for (int polygonIndex = 0; polygonIndex < mesh->GetPolygonCount(); polygonIndex++)
				{
					int polygonSize = mesh->GetPolygonSize(polygonIndex);

					for (int i = 0; i < polygonSize; i++)
					{
						int normalIndex = 0;

						if (normalElement->GetReferenceMode() == FbxGeometryElement::eDirect)
							normalIndex = indexByPolygonVertex;
						
						if (normalElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
							normalIndex = normalElement->GetIndexArray().GetAt(indexByPolygonVertex);
						

						FbxDouble3 normal = normalElement->GetDirectArray().GetAt(normalIndex);

						m_normal.push_back(glm::vec3(normal[0], normal[1], normal[2]));

						indexByPolygonVertex++;
					}
				}
			}
		}
	}
	int count = pNode->GetChildCount();
	for (int i = 0; i < count; i++)
	{
		this->SaveUV(pNode->GetChild(i));
	}
}
std::vector<glm::vec3> VertexInfo::GetPos() const
{
	return m_postion;
}

std::vector<glm::vec2> VertexInfo::GetUV() const
{
	return m_uv;
}

std::vector<glm::vec3> VertexInfo::GetNormal() const
{
	return m_normal;
}
