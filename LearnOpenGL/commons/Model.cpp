#include "Model.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include <iostream>
#include "CommonUtils.h"

void Model::LoadModel(std::string path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "Error: Assimp::" << importer.GetErrorString() << std::endl;
		return;
	}

	mModelPath = path.substr(0, path.find_last_of('/'));
	ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; ++i)
	{
		mMeshList.push_back(ProcessMesh(scene->mMeshes[node->mMeshes[i]], scene));
	}

	for (size_t i = 0; i < node->mNumChildren; ++i)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh* Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<MeshTexture> textures;

	for (size_t i = 0; i < mesh->mNumVertices; ++i)
	{
		const auto vertex = mesh->mVertices[i];
		Vertex v;
		v.Position.x = vertex.x;
		v.Position.y = vertex.y;
		v.Position.z = vertex.z;

		if (mesh->HasNormals())
		{
			const auto normal = mesh->mNormals[i];
			v.Normal.x = normal.x;
			v.Normal.y = normal.y;
			v.Normal.z = normal.z;
		}

		if (mesh->mTextureCoords[0])
		{
			v.Texcoord.x = mesh->mTextureCoords[0][i].x;
			v.Texcoord.y = mesh->mTextureCoords[0][i].y;
		}
		else
		{
			v.Texcoord = vec2(0, 0);
		}
		vertices.push_back(v);
	}

	//添加顶点索引
	for (size_t i = 0; i < mesh->mNumFaces; ++i)
	{
		const auto face = mesh->mFaces[i];
		for (size_t j = 0; j < face.mNumIndices; ++j)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	//添加材质
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<MeshTexture> diffuseTextures = LoadMaterialTextures(
			material,
			aiTextureType_DIFFUSE,
			MeshTexture::TextureType::Diffuse
		);
		textures.insert(textures.end(), diffuseTextures.begin(), diffuseTextures.end());

		std::vector<MeshTexture> specularTextures = LoadMaterialTextures(
			material,
			aiTextureType_SPECULAR,
			MeshTexture::TextureType::Specular
		);
		textures.insert(textures.end(), specularTextures.begin(), specularTextures.end());

		std::vector<MeshTexture> normalTextures = LoadMaterialTextures(
			material,
			aiTextureType_NORMALS,
			MeshTexture::TextureType::Normal
		);

		textures.insert(textures.end(), normalTextures.begin(), normalTextures.end());
	}

	return new Mesh(vertices, indices, textures);
}

std::vector<MeshTexture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type,
                                                     MeshTexture::TextureType meshTextureType)
{
	std::vector<MeshTexture> textures;
	for (size_t i = 0; i < mat->GetTextureCount(type); ++i)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		std::string fullPath = CommonUtils::CombinePath(mModelPath, str.C_Str());
		if (IsLoadedTexture(fullPath))
		{
			continue;
		}
		MeshTexture texture(fullPath, GL_REPEAT, meshTextureType);
		textures.push_back(texture);
		mTextureList.push_back(texture);
	}
	return textures;
}

//参数指定的路径的纹理是否已经加载过
bool Model::IsLoadedTexture(const std::string& path)
{
	for (size_t i = 0; i < mTextureList.size(); ++i)
	{
		if (mTextureList[i].Path == path)
		{
			return true;
		}
	}
	return false;
}


void Model::Render(const Shader* pShader)
{
	for (unsigned int i = 0; i < mMeshList.size(); ++i)
	{
		mMeshList[i]->Render(pShader);
	}
}
