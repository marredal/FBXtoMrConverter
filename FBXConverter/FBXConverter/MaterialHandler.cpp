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

					FbxProperty propTexture = material->FindProperty(FbxSurfaceMaterial::sDiffuse);

					Material temp;

					temp.nrOfNormalMaps = 0;
					temp.nrOfTextures = 0;

					int texture_count = propTexture.GetSrcObjectCount<FbxTexture>();
					temp.nrOfTextures = texture_count;
					for (int j = 0; j<texture_count; j++)
					{
						const FbxTexture* texture = FbxCast<FbxTexture>(propTexture.GetSrcObject<FbxTexture>(j));
						// Then, you can get all the properties of the texture, include its name
						const char* texture_name = texture->GetName();

						FbxFileTexture* filetex = (FbxFileTexture*)texture;

						temp.textureFilePath = filetex->GetFileName();

					}

					FbxProperty propNormal = material->FindProperty(FbxSurfaceMaterial::sBump);

					int normal_count = propNormal.GetSrcObjectCount<FbxTexture>();
					temp.nrOfNormalMaps = normal_count;
					for (int j = 0; j<normal_count; j++)
					{
						const FbxTexture* texture = FbxCast<FbxTexture>(propNormal.GetSrcObject<FbxTexture>(j));
						// Then, you can get all the properties of the texture, include its name
						const char* texture_name = texture->GetName();

						FbxFileTexture* filetex = (FbxFileTexture*)texture;

						temp.normalFilePath = filetex->GetFileName();

						std::cout << temp.normalFilePath.c_str() << std::endl;

					}

					//ambient
					lKFbxDouble3 = ((FbxSurfaceLambert *)material)->Ambient;
					temp.ambient = glm::vec3(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2]);

					//diffuse
					lKFbxDouble3 = ((FbxSurfaceLambert *)material)->Diffuse;
					temp.diffuse = glm::vec3(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2]);

					//emissive
					lKFbxDouble3 = ((FbxSurfaceLambert *)material)->Emissive;
					temp.emissive = glm::vec3(lKFbxDouble3.Get()[0], lKFbxDouble3.Get()[1], lKFbxDouble3.Get()[2]);

					//opacity
					lKFbxDouble1 = ((FbxSurfaceLambert *)material)->TransparencyFactor;
					temp.opacity = lKFbxDouble1.Get();

					m_materials.push_back(temp);
					std::cout << m_materials.size() << std::endl;
				}
			}
		}
	}
}


std::vector<Material> MaterialHandler::GetMaterialVector()
{
	return m_materials;
}

int32_t MaterialHandler::GetNumMaterials()
{
	return m_materials.size();
}
