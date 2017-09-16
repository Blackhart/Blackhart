#include <stdlib.h>
#include <stdio.h>

#include <GLFW\glfw3.h>

#include "../export/cpp/Blackhart.hpp"

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
	// ~~~~~ GLFW INITIALIZATION ~~~~~~

	// Initialize glfw
	if (!glfwInit())
		goto EXIT;

	// Set error callback function
	glfwSetErrorCallback(Error_callback);

	// Initialize glfw windows with OpenGL context
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* lWindow = glfwCreateWindow(640, 480, "Models", NULL, NULL);
	if (lWindow == NULL)
		goto GLFW_TERMINATE;
	glfwMakeContextCurrent(lWindow);

	// Set key callback function
	glfwSetKeyCallback(lWindow, key_callback);

	// Set swap interval of the double buffering
	glfwSwapInterval(1);


	// ~~~~~ BLACKHART INITIALIZATION ~~~~~

	// Initialize Blackhart
	if (BK_ERROR(BkInitialize()))
		goto GLFW_DESTROY_WINDOW;

	// Create vertex shader
	BkShader* lVertexShader = BkShader_Create("../../../shaders/vertex.glsl", _BK_VERTEX_SHADER_);
	if (BK_ISNULL(lVertexShader))
		goto BLACKHART_UNINITIALIZE;

	// Create fragment shader
	BkShader* lPixelShader = BkShader_Create("../../../shaders/pixel.glsl", _BK_PIXEL_SHADER_);
	if (BK_ISNULL(lPixelShader))
		goto BLACKHART_RELEASE_VERTEX_SHADER;

	// Create material
	BkMaterial*	lpMaterial = BkMaterial_Create();
	if (BK_ISNULL(lpMaterial))
		goto BLACKHART_RELEASE_PIXEL_SHADER;

	// Attach vertex and fragment shader to the material
	BkMaterial_AttachShader(lpMaterial, lVertexShader);
	BkMaterial_AttachShader(lpMaterial, lPixelShader);

	// Compile the vertex and fragment shader attached to the material
	BkMaterial_CompileShader(lpMaterial);

	// Create GPU Buffer containing triangle's vertices
	real	lVertices[12] = { 0.25f, -0.25f, 0.5f, 1.0f,
							  -0.25f, -0.25f, 0.5f, 1.0f,
							  0.25f, 0.25f, 0.5f, 1.0f };
	BkBuffer*	lpBuffer = BkBuffer_Create(sizeof(lVertices), lVertices);
	if (BK_ISNULL(lpBuffer))
		goto BLACKHART_RELEASE_MATERIAL;


	// ~~~~~ RENDER LOOP ~~~~~

	uint32	lWidth = 0;
	uint32	lHeight = 0;
	while (!glfwWindowShouldClose(lWindow))
	{
		glfwGetFramebufferSize(lWindow, (int*)&lWidth, (int*)&lHeight);
		glViewport(0, 0, lWidth, lHeight);

		BkRender(lpBuffer, lpMaterial);

		glfwSwapBuffers(lWindow);
		glfwPollEvents();
	}


	// ~~~~~ BLACKHART UNINITIALIZATION ~~~~~

BLACKHART_RELEASE_BUFFER:
	BkBuffer_Release(&lpBuffer);

BLACKHART_RELEASE_MATERIAL:
	BkMaterial_Release(&lpMaterial);

BLACKHART_RELEASE_PIXEL_SHADER:
	BkShader_Release(&lPixelShader);

BLACKHART_RELEASE_VERTEX_SHADER:
	BkShader_Release(&lVertexShader);

BLACKHART_UNINITIALIZE:
	BkUninitialize();


	// ~~~~~ GLFW UNINITIALIZATION ~~~~~

GLFW_DESTROY_WINDOW:
	glfwDestroyWindow(lWindow);

GLFW_TERMINATE:
	glfwTerminate();

EXIT:
	return EXIT_SUCCESS;
}