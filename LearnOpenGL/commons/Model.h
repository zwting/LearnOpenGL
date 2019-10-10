#pragma once
#include "../graphic/Shader.h"
#include <vector>
#include "Mesh.h"
#include "assimp/scene.h"

class Model
{
private:
	std::vector<Mesh*> mMeshList;
	std::vector<MeshTexture> mTextureList;
	std::string mModelPath;

	void LoadModel(std::string path);
	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<MeshTexture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type,
	                                              MeshTexture::TextureType meshTextureType);
	bool IsLoadedTexture(const std::string& path);
public:
	std::vector<Mesh*> GetMeshList() const
	{
		return mMeshList;
	}

public:
	Model(std::string path)
	{
		LoadModel(path);
	}

	void Render(const Shader* pShader);
};
