#ifndef  __MESHPROCESSOR_H__
#define __MESHPROCESSOR_H__

#include <fbxsdk.h>
#include <iostream>

class MeshProcessor
{
public:
	MeshProcessor();
	virtual ~MeshProcessor();

	// Process control points
	void ControlPoints(FbxNode* Node);
};

#endif // ! __MESHPROCESSOR_H__