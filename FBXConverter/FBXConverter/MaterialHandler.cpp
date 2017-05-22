#include "MaterialHandler.h"



MaterialHandler::MaterialHandler()
{
}


MaterialHandler::~MaterialHandler()
{
}

void MaterialHandler::ImportMaterial(FbxNode * pNode)
{
	int materialCount = 0;

	FbxPropertyT<FbxDouble3> lKFbxDouble3;
	FbxPropertyT<FbxDouble> lKFbxDouble1;

	FbxNode* childNode = 0;


	childNode = pNode;
	FbxMesh* mesh = childNode->GetMesh();

	if (mesh != NULL)
	{
		materialCount = mesh->GetElementMaterialCount();

		if (materialCount > 0)
		{
			for (int i = 0; i < materialCount; i++)
			{
				FbxSurfaceMaterial *material = pNode->GetMaterial(i);

				if (material->GetClassId().Is(FbxSurfaceLambert::ClassId))
				{

					FbxProperty prop = material->FindProperty(FbxSurfaceMaterial::sDiffuse);

					Material temp;

					int texture_count = prop.GetSrcObjectCount<FbxTexture>();
					for (int j = 0; j<texture_count; j++)
					{
						const FbxTexture* texture = FbxCast<FbxTexture>(prop.GetSrcObject<FbxTexture>(j));
						// Then, you can get all the properties of the texture, include its name
						const char* texture_name = texture->GetName();

						FbxFileTexture* filetex = (FbxFileTexture*)texture;

						temp.m_textureFilePath = filetex->GetFileName();

					}

					//ambient
					lKFbxDouble3 = ((FbxSurfaceLambert *)material)->Ambient;
					temp.m_ambient = glm::vec3(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2]);

					//diffuse
					lKFbxDouble3 = ((FbxSurfaceLambert *)material)->Diffuse;
					temp.m_diffuse = glm::vec3(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2]);

					//emissive
					lKFbxDouble3 = ((FbxSurfaceLambert *)material)->Emissive;
					temp.m_emissive = glm::vec3(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2]);

					//opacity
					lKFbxDouble1 = ((FbxSurfaceLambert *)material)->TransparencyFactor;
					temp.m_opacity = lKFbxDouble1.Get();

					m_materials.push_back(temp);
				}
			}
		}
	}
}


MaterialHandler::Material MaterialHandler::GetMaterial(int i)
{
	return m_materials[i];
}


int32_t MaterialHandler::GetNumMaterials()
{
	return m_materials.size();
}
