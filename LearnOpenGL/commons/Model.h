#pragma once
#include "../graphic/Shader.h"
#include <vector>
#include "Mesh.h"
#include "assimp/scene.h"

class Model
{
private:
	std::vector<Mesh*> meshList;
	std::vector<MeshTexture> textureList;
	std::string modelPath;

	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<MeshTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
	                                              MeshTexture::TextureType meshTextureType);
	bool isLoadedTexture(const std::string path);
public:
	std::vector<Mesh*> getMeshList() const
	{
		return meshList;
	}

public:
	Model(std::string path)
	{
		loadModel(path);
	}

	void Render(const Shader* pShader);
};
