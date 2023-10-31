#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "render.h"

GLFWwindow* InitGL()
{
	// ��ʼ��glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// ��ʼ������
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL005", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Fail to create a window" << std::endl;
		glfwTerminate();
		return NULL;
	}

	// ����������
	glfwMakeContextCurrent(window);

	// ����opengl���� Ҫ������������֮��
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Fail to initialize glad" << std::endl;
		glfwTerminate();
		return NULL;
	}
	// ������ֱͬ��
	glfwSwapInterval(1);

	// �����ӿ�
	GLCall(glViewport(0, 0, WIDTH, HEIGHT));

	// ��׽cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// �����ص�����
	void framebuffer_size_callback(GLFWwindow * window, int width, int height);
	void scroll_callback(GLFWwindow * window, double offsetx, double offsery);
	void mouse_callback(GLFWwindow * window, double xpos, double ypos);
	void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode);

	void ProcessInput(GLFWwindow * window);
	// ע��ص�����
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, key_callback);

	GLCall(glEnable(GL_DEPTH_TEST));					// ��ȼ��
	GLCall(glClearColor(0.2f,0.2f,0.2f, 1.f));			//������ɫ

	return window;
}

