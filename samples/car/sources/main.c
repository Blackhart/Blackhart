#include <GLFW\glfw3.h>
#include <blackhart.h>

#include <stdlib.h>

static void key_callback(GLFWwindow* pWindow, int pKey, int pScancode, int pAction, int pMods)
{
	if (pKey == GLFW_KEY_ESCAPE && pAction == GLFW_PRESS)
		glfwSetWindowShouldClose(pWindow, GLFW_TRUE);
}

void	Error_callback(int pError, const char* pMsg)
{
}

int	main()
{
	if (!glfwInit())
		return 0;
	BkGraphicsInfo lGraphicsInfo;
	lGraphicsInfo.api = BK_GRAPHICS_API_VULKAN;
	lGraphicsInfo.extensions = NULL;
	lGraphicsInfo.extensionCount = 0;
	BkInitialize(&lGraphicsInfo);
	glfwSetErrorCallback(Error_callback);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	GLFWwindow* lWindow = glfwCreateWindow(640, 480, "Models", NULL, NULL);
	if (lWindow == NULL)
	{
		glfwTerminate();
		return 0;
	}
	glfwSetKeyCallback(lWindow, key_callback);
	while (!glfwWindowShouldClose(lWindow))
	{
		glfwPollEvents();
	}
	glfwDestroyWindow(lWindow);
	glfwTerminate();
	return 1;
}