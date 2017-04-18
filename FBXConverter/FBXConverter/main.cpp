#include "Manager.h"
#include <iostream>
#pragma comment(lib, "libfbxsdk.lib")

////Tab character ("\t") counter
//int numTabs = 0;
//static bool gVerbose = true;
//
//void GetPositionInfo(FbxNode* pNode)
//{
//	if (!pNode)
//		return;
//
//	//get mesh
//	FbxMesh* lMesh = pNode->GetMesh();
//	if (lMesh)
//	{
//		//print mesh node name
//		printf("<node: '%s'>\n", pNode->GetName());
//
//		for (int j = 0; j < lMesh->GetControlPointsCount(); j++)
//		{
//			printf("\tVertex[%i].Position:\t'(%f, %f, %f)'\n",
//				j,
//				lMesh->GetControlPointAt(j).mData[0],
//				lMesh->GetControlPointAt(j).mData[1],
//				lMesh->GetControlPointAt(j).mData[2]
//			);
//		}
//		printf("<node>\n");
//	}
//	//recursively traverse each node in the scene
//	int lCount = pNode->GetChildCount();
//	for (int i = 0; i < lCount; i++)
//	{
//		GetPositionInfo(pNode->GetChild(i));
//	}
//}
//
//void GetUVInfo(FbxNode* pNode)
//{
//	if (!pNode)
//		return;
//
//	//get mesh
//	FbxMesh* lMesh = pNode->GetMesh();
//	if (lMesh)
//	{
//		//print mesh node name
//		printf("<node: '%s'>\n", pNode->GetName());
//
//		//get all UV set names
//		FbxStringList lUVSetNameList;
//		lMesh->GetUVSetNames(lUVSetNameList);
//		//iterating over all uv sets
//		for (int lUVSetIndex = 0; lUVSetIndex < lUVSetNameList.GetCount(); lUVSetIndex++)
//		{
//			//get lUVSetIndex-th uv set
//			const char* lUVSetName = lUVSetNameList.GetStringAt(lUVSetIndex);
//			const FbxGeometryElementUV* lUVElement = lMesh->GetElementUV(lUVSetName);
//
//			if (!lUVElement)
//				continue;
//
//			// only support mapping mode eByPolygonVertex and eByControlPoint
//			if (lUVElement->GetMappingMode() != FbxGeometryElement::eByPolygonVertex &&
//				lUVElement->GetMappingMode() != FbxGeometryElement::eByControlPoint)
//				return;
//
//			//index array, where holds the index referenced to the uv data
//			const bool lUseIndex = lUVElement->GetReferenceMode() != FbxGeometryElement::eDirect;
//			const int lIndexCount = (lUseIndex) ? lUVElement->GetIndexArray().GetCount() : 0;
//
//			//iterating through the data by polygon
//			const int lPolyCount = lMesh->GetPolygonCount();
//
//			if (lUVElement->GetMappingMode() == FbxGeometryElement::eByControlPoint)
//			{
//				int lVertexCounter = 0;
//				for (int lPolygonIndex = 0; lPolygonIndex < lPolyCount; ++lPolygonIndex)
//				{
//					// build the max index array that we need to pass into MakePoly
//					const int lPolySize = lMesh->GetPolygonSize(lPolygonIndex);
//					for (int i = 0; i < lPolySize; ++i)
//					{
//						FbxVector2 lUVValue;
//
//						//get the index of the current vertex in control points array
//						int lPolyVertIndex = lMesh->GetPolygonVertex(lPolygonIndex, i);
//
//						//the UV index depends on the reference mode
//						int lUVIndex = lUseIndex ? lUVElement->GetIndexArray().GetAt(lPolyVertIndex) : lPolyVertIndex;
//
//						lUVValue = lUVElement->GetDirectArray().GetAt(lUVIndex);
//
//						//User TODO:
//						printf("\tPoint[i%].UV: %f, %f \n", lVertexCounter, lVertexCounter, lUVValue[0], lUVValue[1]);
//						lVertexCounter++;
//						//Print out the value of UV(lUVValue) or log it to a file
//					}
//				}
//			}
//			else if (lUVElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
//			{
//				int lVertexCounter = 0;
//				for (int lPolygonIndex = 0; lPolygonIndex < lPolyCount; ++lPolygonIndex)
//				{
//					// build the max index array that we need to pass into MakePoly
//					const int lPolySize = lMesh->GetPolygonSize(lPolygonIndex);
//					for (int i = 0; i < lPolySize; ++i)
//					{
//						if (lVertexCounter < lIndexCount)
//						{
//							FbxVector2 lUVValue;
//
//							//the UV index depends on the reference mode
//							int lUVIndex = lUseIndex ? lUVElement->GetIndexArray().GetAt(lVertexCounter) : lVertexCounter;
//
//							lUVValue = lUVElement->GetDirectArray().GetAt(lUVIndex);
//
//							//User TODO:
//							//Print out the value of UV(lUVValue) or log it to a file
//							printf("\tP[%i]Point[%i].UV:\t'(%f, %f)' \n", lPolygonIndex, lVertexCounter, i, lUVValue[0], lUVValue[1]);
//							lVertexCounter++;
//						}
//					}
//				}
//			}
//		}
//		printf("<node>\n");
//	}
//	//recursively traverse each node in the scene
//	int lCount = pNode->GetChildCount();
//	for (int i = 0; i < lCount; i++)
//	{
//		GetUVInfo(pNode->GetChild(i));
//	}
//}
//
//void GetNormalInfo(FbxNode* pNode)
//{
//	if (!pNode)
//		return;
//
//	//get mesh
//	FbxMesh* lMesh = pNode->GetMesh();
//	if (lMesh)
//	{
//		//print mesh node name
//		printf("<node: '%s'>\n", pNode->GetName());
//
//		//get the normal element
//		FbxGeometryElementNormal* lNormalElement = lMesh->GetElementNormal();
//		FbxGeometryElementTangent* lTangentElement = lMesh->GetElementTangent();
//		FbxGeometryElementBinormal* lBinormalElement = lMesh->GetElementBinormal();
//		//lMesh->GetControlPointsCount()
//
//		if (lNormalElement)
//		{
//			//mapping mode is by control points. The mesh should be smooth and soft.
//			//we can get normals by retrieving each control point
//			if (lNormalElement->GetMappingMode() == FbxGeometryElement::eByControlPoint)
//			{
//				int vertexCounter = 0;
//				//Let's get normals of each vertex, since the mapping mode of normal element is by control point
//				for (int lVertexIndex = 0; lVertexIndex < lMesh->GetControlPointsCount(); lVertexIndex++)
//				{
//					int lNormalIndex = 0;
//					//reference mode is direct, the normal index is same as vertex index.
//					//get normals by the index of control vertex
//					if (lNormalElement->GetReferenceMode() == FbxGeometryElement::eDirect)
//						lNormalIndex = lVertexIndex;
//
//					//reference mode is index-to-direct, get normals by the index-to-direct
//					if (lNormalElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
//						lNormalIndex = lNormalElement->GetIndexArray().GetAt(lVertexIndex);
//
//					//Got normals of each vertex.  \tVertex[%i].Position:\t'(%f, %f, %f)'\n
//					FbxDouble3 lNormal = lNormalElement->GetDirectArray().GetAt(lNormalIndex);
//					if (gVerbose) printf("\tPoint[%i].Normal:\t'(%f, %f, %f)'\n", vertexCounter, lVertexIndex, lNormal[0], lNormal[1], lNormal[2]);
//					vertexCounter++;
//					//add your custom code here, to output normals or get them into a list, such as KArrayTemplate<FbxVector4>
//					//. . .
//				}//end for lVertexIndex
//			}//end eByControlPoint
//			 //mapping mode is by polygon-vertex.
//			 //we can get normals by retrieving polygon-vertex.
//			else if (lNormalElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
//			{
//				int lVertexCounter = 0;
//				int lIndexByPolygonVertex = 0;
//				//Let's get normals of each polygon, since the mapping mode of normal element is by polygon-vertex.
//				for (int lPolygonIndex = 0; lPolygonIndex < lMesh->GetPolygonCount(); lPolygonIndex++)
//				{
//					//get polygon size, you know how many vertices in current polygon.
//					int lPolygonSize = lMesh->GetPolygonSize(lPolygonIndex);
//					//retrieve each vertex of current polygon.
//					for (int i = 0; i < lPolygonSize; i++)
//					{
//						int lNormalIndex = 0;
//						//reference mode is direct, the normal index is same as lIndexByPolygonVertex.
//						if (lNormalElement->GetReferenceMode() == FbxGeometryElement::eDirect)
//							lNormalIndex = lIndexByPolygonVertex;
//
//						//reference mode is index-to-direct, get normals by the index-to-direct
//						if (lNormalElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
//							lNormalIndex = lNormalElement->GetIndexArray().GetAt(lIndexByPolygonVertex);
//
//						//Got normals of each polygon-vertex.
//						FbxDouble3 lNormal = lNormalElement->GetDirectArray().GetAt(lNormalIndex);
//						if (gVerbose) printf("\tP[%i]Point[%i].Normal:\t'(%f, %f, %f)'\n", lPolygonIndex, lVertexCounter, lNormal[0], lNormal[1], lNormal[2]);
//						lVertexCounter++;
//						//add your custom code here, to output normals or get them into a list, such as KArrayTemplate<FbxVector4>
//						//. . .
//
//						lIndexByPolygonVertex++;
//					}//end for i //lPolygonSize
//				}//end for lPolygonIndex //PolygonCount
//
//			}//end eByPolygonVertex
//		}//end if lNormalElement
//
//
//		if (lTangentElement)
//		{
//			//mapping mode is by control points. The mesh should be smooth and soft.
//			//we can get tangents by retrieving each control point
//			if (lTangentElement->GetMappingMode() == FbxGeometryElement::eByControlPoint)
//			{
//				int vertexCounter = 0;
//				//Let's get tangents of each vertex, since the mapping mode of tangent element is by control point
//				for (int lVertexIndex = 0; lVertexIndex < lMesh->GetControlPointsCount(); lVertexIndex++)
//				{
//					int lTangetIndex = 0;
//					//reference mode is direct, the tangent index is same as vertex index.
//					//get tangents by the index of control vertex
//					if (lTangentElement->GetReferenceMode() == FbxGeometryElement::eDirect)
//						lTangetIndex = lVertexIndex;
//
//					//reference mode is index-to-direct, get tangents by the index-to-direct
//					if (lTangentElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
//						lTangetIndex = lTangentElement->GetIndexArray().GetAt(lVertexIndex);
//
//					//Got tangents of each vertex.
//					FbxDouble3 lTangent = lTangentElement->GetDirectArray().GetAt(lTangetIndex);
//					if (gVerbose) printf("\tPoint[%i].Tangent:\t'(%f, %f, %f)'\n", vertexCounter, lTangent[0], lTangent[1], lTangent[2]);
//					vertexCounter++;
//					//add your custom code here, to output tangents or get them into a list, such as KArrayTemplate<FbxVector4>
//					//. . .
//				}//end for lVertexIndex
//			}//end eByControlPoint
//			 //mapping mode is by polygon-vertex.
//			 //we can get tangents by retrieving polygon-vertex.
//			else if (lTangentElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
//			{
//				int vertexCounter = 0;
//				int lIndexByPolygonVertex = 0;
//				//Let's get tangents of each polygon, since the mapping mode of tangent element is by polygon-vertex.
//				for (int lPolygonIndex = 0; lPolygonIndex < lMesh->GetPolygonCount(); lPolygonIndex++)
//				{
//					//get polygon size, you know how many vertices in current polygon.
//					int lPolygonSize = lMesh->GetPolygonSize(lPolygonIndex);
//					//retrieve each vertex of current polygon.
//					for (int i = 0; i < lPolygonSize; i++)
//					{
//						int lTangetIndex = 0;
//						//reference mode is direct, the tangent index is same as lIndexByPolygonVertex.
//						if (lTangentElement->GetReferenceMode() == FbxGeometryElement::eDirect)
//							lTangetIndex = lIndexByPolygonVertex;
//
//						//reference mode is index-to-direct, get tangents by the index-to-direct
//						if (lTangentElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
//							lTangetIndex = lTangentElement->GetIndexArray().GetAt(lIndexByPolygonVertex);
//
//						//Got tangents of each polygon-vertex.
//						FbxDouble3 lTangent = lTangentElement->GetDirectArray().GetAt(lTangetIndex);
//						if (gVerbose) printf("\tP[%i]Point[%i].Tangent:\t'(%f, %f, %f)'\n", lPolygonIndex, vertexCounter, i, lTangent[0], lTangent[1], lTangent[2]);
//						vertexCounter++;
//						//add your custom code here, to output tangents or get them into a list, such as KArrayTemplate<FbxVector4>
//						//. . .
//
//						lIndexByPolygonVertex++;
//					}//end for i //lPolygonSize
//				}//end for lPolygonIndex //PolygonCount
//
//			}//end eByPolygonVertex
//		}//end if lTangentElement
//
//
//		if (lBinormalElement)
//		{
//			//mapping mode is by control points. The mesh should be smooth and soft.
//			//we can get binormals by retrieving each control point
//			if (lBinormalElement->GetMappingMode() == FbxGeometryElement::eByControlPoint)
//			{
//				int vertexCounter = 0;
//				//Let's get binormals of each vertex, since the mapping mode of binormal element is by control point
//				for (int lVertexIndex = 0; lVertexIndex < lMesh->GetControlPointsCount(); lVertexIndex++)
//				{
//					int lBinormalIndex = 0;
//					//reference mode is direct, the binormal index is same as vertex index.
//					//get normals by the index of control vertex
//					if (lBinormalElement->GetReferenceMode() == FbxGeometryElement::eDirect)
//						lBinormalIndex = lVertexIndex;
//
//					//reference mode is index-to-direct, get binormals by the index-to-direct
//					if (lBinormalElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
//						lBinormalIndex = lBinormalElement->GetIndexArray().GetAt(lVertexIndex);
//
//					//Got binormals of each vertex.
//					FbxDouble3 lBinormal = lBinormalElement->GetDirectArray().GetAt(lBinormalIndex);
//					if (gVerbose) printf("\tPoint[%i].Bi-Tan:\t'(%f, %f, %f)'\n", lVertexIndex, lBinormal[0], lBinormal[1], lBinormal[2]);
//					vertexCounter++;
//					//add your custom code here, to output binormals or get them into a list, such as KArrayTemplate<FbxVector4>
//					//. . .
//				}//end for lVertexIndex
//			}//end eByControlPoint
//			 //mapping mode is by polygon-vertex.
//			 //we can get binormals by retrieving polygon-vertex.
//			else if (lBinormalElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
//			{
//				int vertexCounter = 0;
//				int lIndexByPolygonVertex = 0;
//				//Let's get binormals of each polygon, since the mapping mode of binormal element is by polygon-vertex.
//				for (int lPolygonIndex = 0; lPolygonIndex < lMesh->GetPolygonCount(); lPolygonIndex++)
//				{
//					//get polygon size, you know how many vertices in current polygon.
//					int lPolygonSize = lMesh->GetPolygonSize(lPolygonIndex);
//					//retrieve each vertex of current polygon.
//					for (int i = 0; i < lPolygonSize; i++)
//					{
//						int lBinormalIndex = 0;
//						//reference mode is direct, the binormal index is same as lIndexByPolygonVertex.
//						if (lBinormalElement->GetReferenceMode() == FbxGeometryElement::eDirect)
//							lBinormalIndex = lIndexByPolygonVertex;
//
//						//reference mode is index-to-direct, get binormal by the index-to-direct
//						if (lBinormalElement->GetReferenceMode() == FbxGeometryElement::eIndexToDirect)
//							lBinormalIndex = lBinormalElement->GetIndexArray().GetAt(lIndexByPolygonVertex);
//
//						//Got binormals of each polygon-vertex.
//						FbxDouble3 lBinormal = lBinormalElement->GetDirectArray().GetAt(lBinormalIndex);
//						if (gVerbose) printf("\tP[%i]Point[%i].Bi-Tan:\t'(%f, %f, %f)'\n", lPolygonIndex, vertexCounter, lBinormal[0], lBinormal[1], lBinormal[2]);
//						vertexCounter++;
//						//add your custom code here, to output binormals or get them into a list, such as KArrayTemplate<FbxVector4>
//						//. . .
//
//						lIndexByPolygonVertex++;
//					}//end for i //lPolygonSize
//				}//end for lPolygonIndex //PolygonCount
//
//			}//end eByPolygonVertex
//		}//end if lBinormalElement
//		printf("<node>\n");
//	}//end if lMesh
//	 //recursively traverse each node in the scene
//	int lCount = pNode->GetChildCount();
//	for (int i = 0; i < lCount; i++)
//	{
//		GetNormalInfo(pNode->GetChild(i));
//	}
//}
//
////Main function - loads the hard-coded fbx file,
////and prints its contents in an xml format to stdout.

int main(int argc, char** argv) {

	Manager m_mananger;

	m_mananger.Init();

	m_mananger.Run();

	getchar();
	return 0;
}