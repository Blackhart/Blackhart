// GLFW library headers.
#include <GLFW\glfw3.h>

// Blackhart-Editor headers.
#include "foundation\BkTime.hpp"

// ~~~~~ Def(INTERNAL) ~~~~~

static double __time = 0.0;
static double __delta_time = 0.0;

// ~~~~~ Def(PUBLIC) ~~~~~

void	BkTime_Update()
{
	double time = glfwGetTime();

	__delta_time = time - __time;
	
	__time = time;
}

double	BkTime_DeltaTime()
{
	return __delta_time;
}