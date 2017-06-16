#include <GLFW\glfw3.h>
#include <blackhart.h>

#include <stdlib.h>
#include <stdio.h>

static void	key_callback(GLFWwindow* pWindow, int pKey, int pScancode, int pAction, int pMods)
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

	glfwSetErrorCallback(Error_callback);

	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* lWindow = glfwCreateWindow(640, 480, "Models", NULL, NULL);
	if (lWindow == NULL)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(lWindow);

	BkGraphicsInfo lGraphicsInfo;
	lGraphicsInfo.api = BK_GRAPHICS_API_OPENGL;
	if (BkInitialize(&lGraphicsInfo) != 0)
		return -1;

	BkShader* lVertexShader = NULL;
	BkShader* lPixelShader = NULL;
	if (BkCreateShader(&lVertexShader, "../../../shaders/vertex.glsl") != 0)
		return -1;
	if (BkCreateShader(&lPixelShader, "../../../shaders/pixel.glsl") != 0)
		return -1;

	BkReleaseShader(&lPixelShader);
	BkReleaseShader(&lVertexShader);

	glfwSetKeyCallback(lWindow, key_callback);
	glfwSwapInterval(1);

	uint32	lWidth = 0;
	uint32	lHeight = 0;
	while (!glfwWindowShouldClose(lWindow))
	{
		glfwGetFramebufferSize(lWindow, &lWidth, &lHeight);
		glViewport(0, 0, lWidth, lHeight);
		glfwSwapBuffers(lWindow);
		glfwPollEvents();
		BkRender();
	}

	BkUninitialize();
	glfwDestroyWindow(lWindow);
	glfwTerminate();
	return 0;
}