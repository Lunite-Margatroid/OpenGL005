#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "render.h"

GLFWwindow* InitGL()
{
	// 初始化glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// 初始化窗口
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL005", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Fail to create a window" << std::endl;
		glfwTerminate();
		return NULL;
	}

	// 生成上下文
	glfwMakeContextCurrent(window);

	// 加载opengl函数 要在生成上下文之后
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Fail to initialize glad" << std::endl;
		glfwTerminate();
		return NULL;
	}
	// 开启垂直同步
	glfwSwapInterval(1);

	// 设置视口
	GLCall(glViewport(0, 0, WIDTH, HEIGHT));

	// 捕捉cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// 声明回调函数
	void framebuffer_size_callback(GLFWwindow * window, int width, int height);
	void scroll_callback(GLFWwindow * window, double offsetx, double offsery);
	void mouse_callback(GLFWwindow * window, double xpos, double ypos);
	void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode);

	void ProcessInput(GLFWwindow * window);
	// 注册回调函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, key_callback);

	GLCall(glEnable(GL_DEPTH_TEST));					// 深度检测
	GLCall(glClearColor(0.2f,0.2f,0.2f, 1.f));			//清屏颜色

	return window;
}

