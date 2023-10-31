#version 330 core
// ���Դ
// ����struct
struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

// ����
// �����
struct DirLight
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 direction;
};

// ���Դ
struct PointLight
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 position;

	float kConstant;		// ������
	float kLinear;			// һ����
	float kQuadratic;		// 2����
};


// �۹�
struct SpotLight
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	vec3 position;
	vec3 direction;
	
	// ����߽�
	float innerbdr;
	float outerbdr;

	// ˥��
	float kConstant;		// ������
	float kLinear;			// һ����
	float kQuadratic;		// 2����
};

in vec3 normal;				// ���Զ������Եķ�����
in vec3 fragPos;			// Ƭ������
in vec2 TexCoord;			// ��������

out vec4 FragColor;			// outputƬ����ɫ

uniform Material material;	// ����

uniform DirLight dirLight;						// �����Դ
#define N_POINTLIGHT 4
uniform PointLight pointLight[N_POINTLIGHT];	// ���Դ
uniform SpotLight spotLight;					// �۹�
uniform mat3 normalMat;							// ���߾��� �޸��ǵȱ�������ɵ��α�
uniform vec3 viewPos;							// �۲���λ�� ���ڼ��㷴���

vec3 ProcDirectionLight(DirLight light, vec3 texDiff, vec3 texSpec, vec3 normalVec, vec3 viewDir);
vec3 ProcPointLight(PointLight light, vec3 texDiff, vec3 texSpec, vec3 normalVec, vec3 viewDir);
vec3 ProcSpotLight(SpotLight light, vec3 texDiff, vec3 texSpec, vec3 normalVec, vec3 viewDir);
void main()
{
	// ���㷨��������λ��
	vec3 norm = normalMat * normal;
	norm = normalize(norm);
	// ����Ƭ�β���
	vec3 texDiff = vec3(texture(material.diffuse, TexCoord));
	vec3 texSpec = vec3(texture(material.specular, TexCoord));
	// ��Ƭ��ָ��۲���
	vec3 viewDir = normalize(fragPos-viewPos);

	vec3 result = vec3(0.0, 0.0, 0.0);

	// �����
	result += ProcDirectionLight(dirLight, texDiff, texSpec, norm, viewDir);

	// ���Դ
	int i = 0;
	for (; i < N_POINTLIGHT; i++)
	{
		result += ProcPointLight(pointLight[i], texDiff, texSpec, norm, viewDir);
	}

	// �۹�
	result += ProcSpotLight(spotLight,texDiff,texSpec, norm, viewDir);

	FragColor = vec4(result, 1.0);
}

vec3 ProcDirectionLight(DirLight light, vec3 texDiff, vec3 texSpec, vec3 normalVec, vec3 viewDir)
{
	vec3 output;
	// ���߷���
	vec3 lightDir = normalize(-light.direction);

	// ���㻷����
	vec3 ambient = light.ambient * texDiff;	// ����Ļ����ⷴ�����������ɫһ��

	// ����ɢ���
	float diff = max(dot(lightDir, normalVec), 0.0);	// �������ǿ��ϵ��
	vec3 diffuse = diff * light.diffuse * texDiff;

	// ���㷴���
	vec3 reflectDir = reflect(-lightDir, normalVec);					// ���������
	float spec = pow(max(dot(reflectDir, viewDir), 0.0), material.shininess);	// ����ǿ��
	vec3 specular = texSpec * spec * light.specular;	// �������ɫ

	output = ambient + diffuse + specular;
	return output;
}

vec3 ProcPointLight(PointLight light, vec3 texDiff, vec3 texSpec, vec3 normalVec, vec3 viewDir)
{
	// ���㻷����
	vec3 ambient = light.ambient * texDiff;

	// �����������
	vec3 lightDir = fragPos - light.position;
	float lightDst = length(lightDir);
	lightDir = normalize(lightDir);
	float diff = max(dot(normalVec , lightDir),0.0f);
	vec3 diffuse = light.diffuse * texDiff * diff;

	// ���㾵�淴��
	vec3 reflectDir = reflect(-lightDir, normalVec);
	float spec = pow(max(dot(reflectDir, viewDir), 0.0f), material.shininess);
	vec3 specular = light.specular * texSpec * spec;

	// ����˥��
	float attenuation = 1.0 / 
		(light.kConstant + light.kLinear * lightDst + light.kQuadratic * lightDst * lightDst);

	vec3 output = (ambient + diffuse + specular) * attenuation;
	return output;
}

vec3 ProcSpotLight(SpotLight light, vec3 texDiff, vec3 texSpec, vec3 normalVec, vec3 viewDir)
{
	vec3 output;
	// ���߷���
	vec3 lightDir = light.position - fragPos;
	float lightDst = length(lightDir);
	lightDir = normalize(lightDir);

	// ����Ƭ���Ƿ��ڹ��շ�Χ��
	float theta = dot(lightDir, -normalize(light.direction));

	// ���㻷����
	vec3 ambient = light.ambient * texDiff;

	// Ƭ���ڹ��շ�Χ�� �����㻷����
	output = ambient;

	if (theta >= light.outerbdr)
	{// Ƭ���ڹ��շ�Χ��
		// ����ɢ���
		float diff = max(dot(lightDir, normalVec), 0.0);					// �������ǿ��ϵ��
		vec3 diffuse = diff * light.diffuse * texDiff;

		// ���㷴���
		vec3 reflectDir = reflect(-lightDir, normalVec);					// ���������
		float spec = pow(max(dot(reflectDir, viewDir), 0.0), material.shininess);	// ����ǿ��
		vec3 specular = texSpec * spec * light.specular;	// �������ɫ

		// Ƭ���ڹ��ɴ�
		if (theta < light.innerbdr)
		{
			float attenuation = (theta - light.outerbdr) / (light.innerbdr - light.outerbdr);
			diffuse *= attenuation;
			specular *= attenuation;
		}
		output += diffuse + specular;
	}

	float attenuation = 1.0 /
		(light.kConstant + light.kLinear * lightDst + light.kQuadratic * lightDst * lightDst);
	output *= attenuation;

	return output;
}