#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif

#include <stb/stb_image.h>

#include "render.h"
#include "Camera.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "SpotLight.h"
#include "Model.h"

#include <windows.h>
// ��������
GLFWwindow* InitGL();
void UpdateTimer();
void ProcessInput(GLFWwindow* window);
void RuntimeLog();
// ȫ�ֱ���
float currentTime = 0.0f;
float deltaTime = 0.0f;
float lastTime = 0.0f;

glm::mat4 eMat(1.0f);

LM::Camera camera;

int main()
{
	GLFWwindow* window = InitGL();

	// �߿�ģʽ
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// ģ��·��
	std::string pathNanosuit("L:/OpenGL/model/nanosuit/nanosuit.obj");
	std::string pathLumine("L:/OpenGL/model/lumine/lumine.pmx");

	lastTime = currentTime = glfwGetTime();
	{
		LM::Shader shader("./res/Shader/DiffuseOnlyVertex.shader", "./res/Shader/DiffuseOnlyFragment.shader");
		Alpha::Model model(pathLumine.c_str());

		while (!glfwWindowShouldClose(window))
		{
			glm::mat4 viewTrans = camera.GetViewTrans();
			glm::mat4 projectionTrans = camera.GetProjectionTrans();
			glm::mat4 modelTrans = eMat;
			glm::vec3 cameraPos = camera.GetPosition();

			shader.Bind();
			shader.SetUniformMatrix4f("viewTrans", false, glm::value_ptr(viewTrans));
			shader.SetUniformMatrix4f("projectionTrans", false, glm::value_ptr(projectionTrans));
			shader.SetUniformMatrix4f("modelTrans", false, glm::value_ptr(modelTrans));

			model.Draw(shader);

			// log
			RuntimeLog();
			// ����ʱ�����
			UpdateTimer();
			// ������̿�������
			ProcessInput(window);
			// ��������
			glfwSwapBuffers(window);
			// �����ɫ����ȼ�⻺��
			GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
			// ��鴥���¼�
			glfwPollEvents();
		}
	}
	glfwTerminate();
	return 0;
}

// �ص����� �ı䴰�ڴ�С��λ��ʱ ���������ӿ�
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	GLCall(glViewport(0, 0, WIDTH, HEIGHT));
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	static bool firstMouse = true;
	static float lastX = WIDTH / 2;
	static float lastY = HEIGHT / 2;

	if (firstMouse)
	{
		firstMouse = false;
		lastX = xpos;
		lastY = ypos;
	}

	float offsetX = xpos - lastX;
	float offsetY = lastY - ypos;

	camera.ProcessMouse(offsetX, offsetY);

	lastX = xpos;
	lastY = ypos;
}

void scroll_callback(GLFWwindow* window, double offsetx, double offsety)
{
	camera.ProcessScroll(offsety);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{

}

// ������̽���
void ProcessInput(GLFWwindow* window)
{
	// ���esc���£���رմ���
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera.ProcessKeyInput(LM::FRONT, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera.ProcessKeyInput(LM::BACK, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.ProcessKeyInput(LM::LEFT, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.ProcessKeyInput(LM::RIGHT, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		camera.ProcessKeyInput(LM::UP, deltaTime);
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		camera.ProcessKeyInput(LM::DOWN, deltaTime);
	}
}

void UpdateTimer()
{
	currentTime = glfwGetTime();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;
}

void RuntimeLog()
{
	static glm::vec3 cameraPos = camera.GetPosition();
	cameraPos = camera.GetPosition();
	
	
	std::cout << "Camera current position:" << '(' << cameraPos.x << ',' << cameraPos.y
		<< ',' << cameraPos.z << ")                " << std::endl;


	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	CONSOLE_SCREEN_BUFFER_INFO cursorInfo;
	GetConsoleScreenBufferInfo(hOut, &cursorInfo);
	coord = cursorInfo.dwCursorPosition;
	coord.X = 0;
	coord.Y -= 1;
	SetConsoleCursorPosition(hOut, coord);
}