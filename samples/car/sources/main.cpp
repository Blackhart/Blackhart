#include <new>

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

	// Create GPU Buffer containing triangle's vertices
	real	lVertices[12] = { 0.25f, -0.25f, 0.5f, 1.0f,
							  -0.25f, -0.25f, 0.5f, 1.0f,
							  0.25f, 0.25f, 0.5f, 1.0f };

	uint32 lSize = sizeof(lVertices);

	// Create geometry to store data about the primitive
	BkGeometry* lGeometry = new (std::nothrow) BkGeometry;
	if (lGeometry == NULL)
		goto BLACKHART_UNINITIALIZE;

	lGeometry->vertices = lVertices;

	// Create entity to store the geometry
	BkEntity* lEntity = new (std::nothrow) BkEntity;
	if (lEntity == NULL)
		goto BLACKHART_DESTROY_GEOMETRY;

	lEntity->geometry = lGeometry;

	// Add the entity to the scene
	BkScene_AddEntity(lEntity);


	// ~~~~~ RENDER LOOP ~~~~~

	uint32	lWidth = 0;
	uint32	lHeight = 0;
	while (!glfwWindowShouldClose(lWindow))
	{
		glfwGetFramebufferSize(lWindow, (int*)&lWidth, (int*)&lHeight);
		glViewport(0, 0, lWidth, lHeight);

		BkRender();

		glfwSwapBuffers(lWindow);
		glfwPollEvents();
	}


	// ~~~~~ BLACKHART UNINITIALIZATION ~~~~~

BLACKHART_DESTROY_ENTITY:
	delete lEntity;

BLACKHART_DESTROY_GEOMETRY:
	delete lGeometry;

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