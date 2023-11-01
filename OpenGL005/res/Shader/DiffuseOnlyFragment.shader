#version 330 core
// 多光源
// 材质struct
struct Material
{
	sampler2D texture_diffuse1;
	sampler2D texture_diffuse2;
	sampler2D texture_diffuse3;

	sampler2D texture_specular1;
	sampler2D texture_specular2;
	sampler2D texture_specular3;
	float shininess;
};

// 光照
// 定向光
struct DirLight
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 direction;
};

// 点光源
struct PointLight
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 position;

	float kConstant;		// 常数项
	float kLinear;			// 一次项
	float kQuadratic;		// 2次项
};


// 聚光
struct SpotLight
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 position;
	vec3 direction;

	// 渐变边界
	float innerbdr;
	float outerbdr;

	// 衰减
	float kConstant;		// 常数项
	float kLinear;			// 一次项
	float kQuadratic;		// 2次项
};

in vec3 normal;				// 来自顶点属性的法向量
in vec3 fragPos;			// 片段坐标
in vec2 TexCoord;			// 纹理坐标

out vec4 FragColor;			// output片段颜色

uniform Material material;	// 材质

void main()
{
	FragColor = texture(material.texture_diffuse1, TexCoord);
}