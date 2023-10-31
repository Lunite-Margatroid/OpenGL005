#pragma once
#include "render.h"
#include "Shader.h"
#include <vector>
namespace Alpha
{
	class Mesh
	{
	private:
		unsigned int VAO, VBO, EBO;
		void SetupMesh();
	public:
		std::vector<Vertex> vertice;
		std::vector<unsigned int> indice;
		std::vector<Texture> textures;
		Mesh(std::vector<Vertex> vertice, std::vector<unsigned int> indice, std::vector<Texture> textures);
		void Draw(LM::Shader& shader);
	};
}