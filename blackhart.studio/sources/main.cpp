// Standard library headers.
#include <iostream>
#include <sstream>

// Graphics library headers.
#include <GLFW\glfw3.h>

// blackhart headers.
#include "..\..\blackhart\export\cpp\Blackhart.hpp"

// blackhart.studio headers.
#include "foundation\BkTime.hpp"

// Globales
static struct BkOrbitalCamera   g_camera;
static bool                     g_full_screen = false;

// Constantes
static char const*  APP_TITLE = "Blackhart Studio";

// ~~~~~ Dcl(INTERNAL) ~~~~~

static void InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void MouseCallback(GLFWwindow* window, double posx, double posy);
static void ResizeCallback(GLFWwindow* window, int width, int height);
static void ErrorCallback(int error, const char* msg);
static void ShowFPS(GLFWwindow* window);

// ~~~~~ Def(ALL) ~~~~~

int main()
{
	// ~~~~~ GLFW INITIALIZATION ~~~~~~

	// Initialize glfw
	if (!glfwInit())
		goto EXIT;

	// Set error callback function
	glfwSetErrorCallback(ErrorCallback);

	// Initialize glfw windows and set OpenGL context
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = NULL;

	if (g_full_screen)
	{
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		GLFWvidmode const* vid_mode = glfwGetVideoMode(monitor);
		
		if (vid_mode != NULL)
			window = glfwCreateWindow(vid_mode->width, vid_mode->height, APP_TITLE, monitor, NULL);
	}
	else
	{
		uint16 const window_width = 800;
		uint16 const window_height = 600;

		window = glfwCreateWindow(window_width, window_height, APP_TITLE, NULL, NULL);
	}

	if (window == NULL)
		goto GLFW_TERMINATE;

	glfwMakeContextCurrent(window);

	// Set key callback function
	glfwSetKeyCallback(window, InputCallback);

    // Set mouse callback
    glfwSetCursorPosCallback(window, MouseCallback);

	// Set resize callback function
	glfwSetWindowSizeCallback(window, ResizeCallback);

	// Set swap interval of the double buffering
	glfwSwapInterval(1);


	// ~~~~~ BLACKHART INITIALIZATION ~~~~~

	// Initialize Blackhart
	BkInitialize();

	// Initialize Camera
	BkOrbitalCamera_Initialize(&g_camera);
	struct BkPoint3 const to = BkPoint3_FromXYZ(BK_REAL(0.0), BK_REAL(0.0), BK_REAL(0.0));
	BkOrbitalCamera_SetTarget(&g_camera, &to);
	BkOrbitalCamera_SetRadius(&g_camera, BK_REAL(5));

	// ~~~~~ RENDER LOOP ~~~~~

	// Initialize OpenGL viewport
	int width = 0;
	int height = 0;

	glfwGetWindowSize(window, &width, &height);
	ResizeCallback(window, width, height);

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		BkTime_Update();

		ShowFPS(window);

		glfwPollEvents();

        BkRender(&(g_camera.base));

		glfwSwapBuffers(window);
	}


	// ~~~~~ BLACKHART UNINITIALIZATION ~~~~~

	BkUninitialize();


	// ~~~~~ GLFW UNINITIALIZATION ~~~~~

	glfwDestroyWindow(window);

GLFW_TERMINATE:
	glfwTerminate();

EXIT:
	return EXIT_SUCCESS;
}

void    InputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// ~~~~~ GLFW EVENTS ~~~~~~

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void    MouseCallback(GLFWwindow* window, double posx, double posy)
{
    static double last_mouse_pos[2] = { 0.0, 0.0 };
    static double rotation_zpeed = 20.0;
    static double zoom_speed = 3.0;

    double time = BkTime_DeltaTime();

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == 1)
    {
        double yaw = (posx - last_mouse_pos[0]) * rotation_zpeed * BkTime_DeltaTime();
        double pitch = (posy - last_mouse_pos[1]) * rotation_zpeed * BkTime_DeltaTime();
        BkOrbitalCamera_Rotate(&g_camera, BK_REAL(yaw), BK_REAL(pitch));
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT))
    {
        double dx = (posx - last_mouse_pos[0]) * zoom_speed * BkTime_DeltaTime();
        double dy = (posy - last_mouse_pos[1]) * zoom_speed * BkTime_DeltaTime();
        double radius = dx - dy;
        BkOrbitalCamera_Zoom(&g_camera, BK_REAL(radius));
    }

    last_mouse_pos[0] = posx;
    last_mouse_pos[1] = posy;
}

void    ResizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	g_camera.base.projection = BkProjection_Perspective(BK_REAL(45), BK_REAL(width) / BK_REAL(height), BK_REAL(0.1), BK_REAL(1000));
}

void    ErrorCallback(int error, const char* msg)
{
	std::cout << "Fatal: " << msg << std::endl;
	exit(EXIT_FAILURE);
}

void    ShowFPS(GLFWwindow* window)
{
	static double previous_seconds = 0;
	static int frame_count = 0;

	double elapsed_seconds = 0;

	// Returns number of seconds since GLFW started.
	double currend_seconds = glfwGetTime();

	elapsed_seconds = currend_seconds - previous_seconds;

	// Limit text update 4 times per seconds.
	if (elapsed_seconds > 0.25)
	{
		previous_seconds = currend_seconds;
		double fps = (double)frame_count / elapsed_seconds;
		double ms_per_frame = 1000.0 / fps;

		std::ostringstream out;

		out.precision(3);

		out << std::fixed 
			<< APP_TITLE << "  |  " 
			<< "FPS: " << fps << "  |  " 
			<< "Frame time: " << ms_per_frame << " (ms)";

		glfwSetWindowTitle(window, out.str().c_str());

		frame_count = 0;
	}

	frame_count++;
}