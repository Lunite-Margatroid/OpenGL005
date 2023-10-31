#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <sstream>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <stdlib.h>

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
		x;\
		ASSERT(GLLogCall(#x, __FILE__, __LINE__))

#define WIDTH	800
#define HEIGHT	600

#ifndef PI
#define PI 3.14159f
#endif

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 texCoord;
};

struct Texture
{
	unsigned int id;
	std::string type;
};

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

