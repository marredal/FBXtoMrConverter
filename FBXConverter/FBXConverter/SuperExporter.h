#ifndef __SUPEREXPORTER_H__
#define __SUPEREXPORTER_H__


#include <iostream>


class SuperExporter
{
public:
	SuperExporter();
	virtual ~SuperExporter();

	void Run();
	void Convert();
	void AddMesh();
	void AddSkeleton();
	void AddAnimation();
	void Export();

private:
};


#endif	// ! __SUPEREXPORTER_H__