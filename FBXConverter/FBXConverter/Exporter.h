#ifndef __EXPORTER_H__
#define __EXPORTER_H__
#define FBXSDK_SHARED

#include "ExporterStruct.h"

class Exporter
{
public:
	Exporter();
	virtual ~Exporter();

private:
	FbxManager* manager;
	FbxScene* scene;
	FbxImporter* importer;
};

#endif // !__EXPORTER_H__