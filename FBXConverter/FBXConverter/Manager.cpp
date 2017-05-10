#include "Manager.h"

Manager::Manager()
{
}


Manager::~Manager()
{
}


void Manager::Init(const char* filepath)
{
	const char* m_FilePath = filepath;

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


void Manager::Run(VertexInfo &target)
{
	if (m_root)
	{
		for (int i = 0; i < m_root->GetChildCount(); i++)
		{
			target.SavePosition(m_root->GetChild(i));
			target.SaveUV(m_root->GetChild(i));
			target.SavetNormal(m_root->GetChild(i));
			target.SaveTangent(m_root->GetChild(i));
			target.SaveBiTangent(m_root->GetChild(i));
			target.SaveIndices(m_root->GetChild(i));
			target.GetCustomAttribute(m_root->GetChild(i));
		}
	}
}

void Manager::Run(SkeletonAnimation & target)
{
	target.SetScene(m_Scene);
	target.Export();

}

//std::vector<glm::vec3> Manager::GetPos()
//{
//	return m_vertexInfo.GetPos();
//}

