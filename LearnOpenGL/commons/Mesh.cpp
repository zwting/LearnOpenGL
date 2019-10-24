#include "Mesh.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, std::vector<unsigned>& indices, std::vector<MeshTexture> textures)
{
	this->mVertices = vertices;
	this->mIndices = indices;
	this->mTextures = textures;

	SetupMesh();
}

void Mesh::Render(const Shader* shader)
{
	shader->Use();
	for (unsigned int i = 0; i < mTextures.size(); ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		std::string name = "texture";
		shader->SetInt((name + std::to_string(i)).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, mTextures[i].pTexture->GetID());
	}
	glBindVertexArray(mVAO);
	glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, nullptr);
	glBindVertexArray(0);
}

void Mesh::AddTexture(const MeshTexture& texture)
{
	bool isFind = false;
	for(size_t i = 0;i<mTextures.size();++i)
	{
		if(texture.Path == mTextures[i].Path)
		{
			isFind = true;
			break;
		}
	}
	if(!isFind)
	{
		mTextures.push_back(texture);
	}
}

void Mesh::SetupMesh()
{
	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mEBO);
	glGenBuffers(1, &mVBO);

	glBindVertexArray(mVAO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);

	glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), &mVertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(unsigned int), &mIndices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(0));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, Normal)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
	                      reinterpret_cast<void*>(offsetof(Vertex, Texcoord)));

	glBindVertexArray(0);
}
