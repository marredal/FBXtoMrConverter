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


//..::SAVE FUNCTIONS::..//
void VertexInfo::SavePosition(FbxNode* pNode)
{
	if (!pNode)
		return;

	//get mesh
	FbxMesh* mesh = pNode->GetMesh();
	if (mesh)
	{
		m_numVerts = mesh->GetControlPointsCount();
		for (int i = 0; i < mesh->GetControlPointsCount(); i++)
		{
			glm::vec3 output;
			output.x = mesh->GetControlPointAt(i).mData[0];
			output.y = mesh->GetControlPointAt(i).mData[1];
			output.z = mesh->GetControlPointAt(i).mData[2];
			m_position.push_back(output);
		}
	}
	int count = pNode->GetChildCount();
	for (int i = 0; i < count; i++)
	{
		SavePosition(pNode->GetChild(i));
	}
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
			else if (normalElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
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
void VertexInfo::SaveTangent(FbxNode * pNode)
{
	if (!pNode)
		return;

	FbxMesh* mesh = pNode->GetMesh();
	if (mesh)
	{
		FbxGeometryElementTangent* tangentElement = mesh->GetElementTangent();

		if (tangentElement)
		{
			if (tangentElement->GetMappingMode() == FbxGeometryElement::eByControlPoint)
			{

				for (int vertexIndex = 0; vertexIndex < mesh->GetControlPointsCount(); vertexIndex++)
				{
					int tangentIndex = 0;

					if (tangentElement->GetReferenceMode() == FbxGeometryElement::eDirect)
						tangentIndex = vertexIndex;

					if (tangentElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
						tangentIndex = tangentElement->GetIndexArray().GetAt(vertexIndex);

					FbxDouble3 tangent = tangentElement->GetDirectArray().GetAt(tangentIndex);

					m_tangent.push_back(glm::vec3(tangent[0], tangent[1], tangent[2]));
				}
			}
			else if (tangentElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
			{
				int indexByPolygonVertex = 0;

				for (int polygonIndex = 0; polygonIndex < mesh->GetPolygonCount(); polygonIndex++)
				{
					int polygonSize = mesh->GetPolygonSize(polygonIndex);

					for (int i = 0; i < polygonSize; i++)
					{
						int tangentIndex = 0;

						if (tangentElement->GetReferenceMode() == FbxGeometryElement::eDirect)
							tangentIndex = indexByPolygonVertex;

						if (tangentElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
							tangentIndex = tangentElement->GetIndexArray().GetAt(indexByPolygonVertex);

						FbxDouble3 tangent = tangentElement->GetDirectArray().GetAt(tangentIndex);

						m_normal.push_back(glm::vec3((float)tangent[i]));
					}
				}
			}
		}
	}
}
void VertexInfo::SaveBiTangent(FbxNode * pNode)
{
	if (!pNode)
		return;

	FbxMesh* mesh = pNode->GetMesh();
	if (mesh)
	{
		FbxGeometryElementBinormal* BiTangentElement = mesh->GetElementBinormal();

		if (BiTangentElement)
		{
			if (BiTangentElement->GetMappingMode() == FbxGeometryElement::eByControlPoint)
			{

				for (int vertexIndex = 0; vertexIndex < mesh->GetControlPointsCount(); vertexIndex++)
				{
					int BITangentIndex = 0;

					if (BiTangentElement->GetReferenceMode() == FbxGeometryElement::eDirect)
						BITangentIndex = vertexIndex;

					if (BiTangentElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
						BITangentIndex = BiTangentElement->GetIndexArray().GetAt(vertexIndex);

					FbxDouble3 biTangent = BiTangentElement->GetDirectArray().GetAt(BITangentIndex);

					m_bitangent.push_back(glm::vec3(biTangent[0], biTangent[1], biTangent[2]));
				}
			}
			else if (BiTangentElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
			{
				int indexByPolygonVertex = 0;

				for (int polygonIndex = 0; polygonIndex < mesh->GetPolygonCount(); polygonIndex++)
				{
					int polygonSize = mesh->GetPolygonSize(polygonIndex);

					for (int i = 0; i < polygonSize; i++)
					{
						int BITangentIndex = 0;

						if (BiTangentElement->GetReferenceMode() == FbxGeometryElement::eDirect)
							BITangentIndex = indexByPolygonVertex;

						if (BiTangentElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
							BITangentIndex = BiTangentElement->GetIndexArray().GetAt(indexByPolygonVertex);

						FbxDouble3 biTangent = BiTangentElement->GetDirectArray().GetAt(BITangentIndex);

						m_bitangent.push_back(glm::vec3((float)biTangent[i]));
					}
				}
			}
		}
	}
}

void VertexInfo::SaveIndices(FbxNode * pNode)
{


	FbxMesh* mesh = pNode->GetMesh();
	if (mesh)
	{
		for (size_t i = 0; i < mesh->GetPolygonVertexCount(); i++)
		{
			m_indices.push_back(mesh->GetPolygonVertices()[i]);

		}
	}
}


void VertexInfo::SaveCustomAttribute(FbxNode* pNode) {


	//If object is a mesh, search for custom attribute
	if (pNode->GetMesh()) {

		if (!pNode)
			return;


		//Get Custom Attribute.		(name of the attribute in Maya.)
		FbxProperty prop = pNode->FindProperty("TestAttrib", false);


		if (prop.IsValid())
		{

			//property name
			std::cout << "custom attribute found: " << prop.GetName() << std::endl;

			//property value
			std::cout << prop.Get<FbxInt>() << std::endl;

			m_customAttributeValue = prop.Get<FbxInt>();
			m_customAttributeName = prop.GetName();

		}
	}
}
void VertexInfo::GetGroups(FbxNode* pNode) {


	//If object is not mesh (it is propably a group)

	if (!pNode->GetMesh()) {

		std::cout << "Group name:" << pNode->GetName() << std::endl;

		m_groupInfo.push_back(pNode->GetName());

		for (int i = 0; i < pNode->GetChildCount(); i++) {

			std::cout << "child name: " << pNode->GetChild(i)->GetName() << std::endl;
			
			//Save the group name and the name of its children.
			m_groupInfo.push_back(pNode->GetChild(i)->GetName());
		}
	}

	
}


//..::GET FUNCTIONS::..//
uint32_t VertexInfo::getCount() const
{
	return m_numVerts;
}
std::vector<glm::vec3> VertexInfo::GetPos() const
{
	return m_position;
}

std::vector<glm::vec2> VertexInfo::GetUV() const
{
	return m_uv;
}

std::vector<glm::vec3> VertexInfo::GetNormal() const
{
	return m_normal;
}

std::vector<glm::vec3> VertexInfo::GetTangent() const
{
	return m_tangent;
}

std::vector<glm::vec3> VertexInfo::GetBiTangent() const
{
	return m_bitangent;
}

std::vector<int> VertexInfo::GetIndices() const
{
	return m_indices;
}

int32_t VertexInfo::GetAttrib()
{
	return m_customAttributeValue;
}
