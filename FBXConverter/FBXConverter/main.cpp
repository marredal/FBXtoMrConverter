#include "Manager.h"
#include "SuperExporter.h"
#include "SkeletonAnimation.h"
#include <iostream>
#include "MrHandler.h"

#pragma comment(lib, "libfbxsdk.lib")


int main(int argc, char** argv) {

	//MrSkelHandler mrHandler;
	//mrHandler.Import(".\\Assets\\Skeletons\\super.mrskel");

	SuperExporter super;
//
	super.Run();

	return 0;
}