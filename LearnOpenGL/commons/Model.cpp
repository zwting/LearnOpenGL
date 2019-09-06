#include "Model.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

void Model::loadModel(std::string path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "Error: Assimp::" << importer.GetErrorString() << std::endl;
		return;
	}

	modelPath = path.substr(0, path.find_last_of('/'));
	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; ++i)
	{
		meshList.push_back(processMesh(scene->mMeshes[node->mMeshes[i]], scene));
	}

	for (size_t i = 0; i < node->mNumChildren; ++i)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh* Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<MeshTexture> textures;

	for (size_t i = 0; i < mesh->mNumVertices; ++i)
	{
		const auto vertex = mesh->mVertices[i];
		Vertex v;
		v.position.x = vertex.x;
		v.position.y = vertex.y;
		v.position.z = vertex.z;

		if (mesh->HasNormals())
		{
			const auto normal = mesh->mNormals[i];
			v.normal.x = normal.x;
			v.normal.y = normal.y;
			v.normal.z = normal.z;
		}

		if (mesh->mTextureCoords[0])
		{
			v.texcoord.x = mesh->mTextureCoords[0][i].x;
			v.texcoord.y = mesh->mTextureCoords[0][i].y;
		}
		else
		{
			v.texcoord = vec2(0, 0);
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
		std::vector<MeshTexture> diffuseTextures = loadMaterialTextures(
			material,
			aiTextureType_DIFFUSE,
			MeshTexture::TextureType::Diffuse
		);

		textures.insert(textures.end(), diffuseTextures.begin(), diffuseTextures.end());

		std::vector<MeshTexture> specularTextures = loadMaterialTextures(
			material,
			aiTextureType_SPECULAR,
			MeshTexture::TextureType::Specular
		);

		textures.insert(textures.end(), specularTextures.begin(), specularTextures.end());

		std::vector<MeshTexture> normalTextures = loadMaterialTextures(
			material,
			aiTextureType_SPECULAR,
			MeshTexture::TextureType::Specular
		);

		textures.insert(textures.end(), normalTextures.begin(), normalTextures.end());
	}

	return new Mesh(vertices, indices, textures);
}

std::vector<MeshTexture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type,
                                                     MeshTexture::TextureType meshTextureType)
{
	std::vector<MeshTexture> textures;
	for (size_t i = 0; i < mat->GetTextureCount(type); ++i)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		if(isLoadedTexture(str.C_Str()))
		{
			continue;
		}
		MeshTexture texture(str.C_Str(), meshTextureType);
		textures.push_back(texture);
		textureList.push_back(texture);
	}
	return textures;
}

//参数指定的路径的纹理是否已经加载过
bool Model::isLoadedTexture(const std::string path)
{
	for(size_t i = 0;i<textureList.size();++i)
	{
		if(textureList[i].path == path)
		{
			return true;
		}
	}
	return false;
}


void Model::Render(const Shader* pShader)
{
	for (unsigned int i = 0; i < meshList.size(); ++i)
	{
		meshList[i]->Render(pShader);
	}
}
