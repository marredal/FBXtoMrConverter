#include "Manager.h"
#include "SuperExporter.h"
#include "SkeletonAnimation.h"
#include <iostream>
#pragma comment(lib, "libfbxsdk.lib")


int main(int argc, char** argv) {

	SuperExporter super;

	super.Run();

	return 0;
}