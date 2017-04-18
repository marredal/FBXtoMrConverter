#include "Manager.h"



Manager::Manager()
{
}


Manager::~Manager()
{
}


void Manager::Init()
{
	const char* m_FilePath = ".\\Assets\\tangentTest.fbx";

	m_Manager = FbxManager::Create();
	FbxIOSettings *ios = FbxIOSettings::Create(m_Manager, IOSROOT);
	//kolla settings o fixa settings
	m_Manager->SetIOSettings(ios);

	m_Importer = FbxImporter::Create(m_Manager, "");

	//set filePath (m_FilePath)
	if (!m_Importer->Initialize(m_FilePath, -1, m_Manager->GetIOSettings())) {
		printf("Call to FbxImporter::Initialize() failed.\n");
		printf("Error returned: %s\n\n", m_Importer->GetStatus().GetErrorString());
		getchar();
		exit(-1);
	}

	m_Scene = FbxScene::Create(m_Manager, "scene");

	m_Importer->Import(m_Scene);

	m_Importer->Destroy();

	m_root = m_Scene->GetRootNode();
}


void Manager::Run()
{
	for (int i = 0; i < m_root->GetChildCount(); i++)
	{
		m_vertexInfo.SetPosition(m_root->GetChild(i));
		m_vertexInfo.SetUV(m_root->GetChild(i));
		m_vertexInfo.SetNormal(m_root->GetChild(i));
	}

}

MeshInfo Manager::GetMesh(MeshInfo info)
{
	info.pos = m_vertexInfo.GetPosition();
	info.nor = m_vertexInfo.GetNormal();
	info.uv = m_vertexInfo.GetUV();

	return info;
}

