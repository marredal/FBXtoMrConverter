#include "fbxsdk.h"
#pragma comment(lib, "libfbxsdk.lib")

int main()
{

	FbxManager* manager = FbxManager::Create();

	manager->Destroy();

	return 0;
}