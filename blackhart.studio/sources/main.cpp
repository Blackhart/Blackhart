// Standard library headers.
#include <cmath>
#include <iostream>
#include <sstream>

// Graphics library headers.
#include <GLFW/glfw3.h>

// blackhart headers.
#include "../../blackhart/export/cpp/Blackhart.hpp"

// blackhart.studio headers.
#include "foundation/BkTime.hpp"

// Globales
static struct BkOrbitalCamera g_camera;
static BkScene* g_scene = NULL;
static BkPointCloud* g_bunny = NULL;
static bool g_full_screen = false;

// Constantes
static char const* APP_TITLE = "Blackhart Studio";
static int const DEPTH_BUFFER_BITS = 24;
static real const CAMERA_FOV_DEG = BK_REAL(45);
static real const CAMERA_FRAME_MARGIN = BK_REAL(1.25);

// ~~~~~ Dcl(INTERNAL) ~~~~~

static void InputCallback(GLFWwindow* window, int key, int scancode, int action,
                          int mods);
static void MouseCallback(GLFWwindow* window, double posx, double posy);
static void ResizeCallback(GLFWwindow* window, int width, int height);
static void ErrorCallback(int error, const char* msg);
static void ShowFPS(GLFWwindow* window);

// ~~~~~ Def(ALL) ~~~~~

int main() {
  // ~~~~~ GLFW INITIALIZATION ~~~~~~

  // Initialize glfw
  if (!glfwInit()) return EXIT_FAILURE;

  // Set error callback function
  glfwSetErrorCallback(ErrorCallback);

  // Initialize glfw windows and set OpenGL context
  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
  glfwWindowHint(GLFW_DEPTH_BITS, DEPTH_BUFFER_BITS);
  // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

  GLFWwindow* window = NULL;

  if (g_full_screen) {
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    GLFWvidmode const* vid_mode = glfwGetVideoMode(monitor);

    if (vid_mode != NULL)
      window = glfwCreateWindow(vid_mode->width, vid_mode->height, APP_TITLE,
                                monitor, NULL);
  } else {
    uint16 const window_width = 800;
    uint16 const window_height = 600;

    window =
        glfwCreateWindow(window_width, window_height, APP_TITLE, NULL, NULL);
  }

  if (window == NULL) {
    glfwTerminate();
    return EXIT_FAILURE;
  }

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

  g_scene = BkScene_Create();
  if (g_scene == NULL) {
    std::cout << "Fatal: failed to create scene" << std::endl;
    BkUninitialize();
    glfwDestroyWindow(window);
    glfwTerminate();
    return EXIT_FAILURE;
  }

  char bunny_path[1024];
  BkFileSystem_CombinePath(bunny_path, BK_DEFAULT_ASSET_PATH, "bunny.ply");
  g_bunny = BkPointCloud_CreateFromPlyFile(bunny_path);
  if (g_bunny == NULL) {
    std::cout << "Fatal: failed to load " << bunny_path << std::endl;
    BkScene_Release(&g_scene);
    BkUninitialize();
    glfwDestroyWindow(window);
    glfwTerminate();
    return EXIT_FAILURE;
  }
  BkScene_AddCloud(g_scene, g_bunny);

  // Frame camera so the whole world AABB stays in view while orbiting
  struct BkAABB const aabb = BkPointCloud_GetWorldAABB(g_bunny);
  struct BkPoint3 const target = BkAABB_Center(&aabb);
  struct BkVector3 const size = BkAABB_Size(&aabb);
  real const bounding_sphere_radius = BkVector3_Magnitude(&size) * BK_REAL(0.5);
  real const half_fov_rad = BkMath_RadFromDeg(CAMERA_FOV_DEG) * BK_REAL(0.5);
  real const radius =
      CAMERA_FRAME_MARGIN * bounding_sphere_radius / BK_REAL(tan(half_fov_rad));

  BkOrbitalCamera_Initialize(&g_camera);
  BkOrbitalCamera_SetTarget(&g_camera, &target);
  BkOrbitalCamera_SetRadius(&g_camera, radius);

  // ~~~~~ RENDER LOOP ~~~~~

  // Initialize OpenGL viewport
  int width = 0;
  int height = 0;
  glfwGetWindowSize(window, &width, &height);
  ResizeCallback(window, width, height);

  // Main loop
  while (!glfwWindowShouldClose(window)) {
    BkTime_Update();

    BkOrbitalCamera_Rotate(&g_camera, BK_REAL(50) * BK_REAL(BkTime_DeltaTime()),
                           BK_REAL(0));

    ShowFPS(window);

    glfwPollEvents();

    BkRender(g_scene, &(g_camera.base));

    glfwSwapBuffers(window);
  }

  // ~~~~~ BLACKHART UNINITIALIZATION ~~~~~

  BkScene_RemoveCloud(g_scene, g_bunny);
  BkPointCloud_Release(&g_bunny);
  BkScene_Release(&g_scene);
  BkUninitialize();

  // ~~~~~ GLFW UNINITIALIZATION ~~~~~

  glfwDestroyWindow(window);

  glfwTerminate();

  return EXIT_SUCCESS;
}

void InputCallback(GLFWwindow* window, int key, int scancode, int action,
                   int mods) {
  (void)mods;
  (void)scancode;
  (void)window;

  // ~~~~~ GLFW EVENTS ~~~~~~

  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void MouseCallback(GLFWwindow* window, double posx, double posy) {
  static double last_mouse_pos[2] = {0.0, 0.0};
  static double rotation_zpeed = 20.0;
  static double zoom_speed = 3.0;

  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == 1) {
    double yaw =
        (posx - last_mouse_pos[0]) * rotation_zpeed * BkTime_DeltaTime();
    double pitch =
        (posy - last_mouse_pos[1]) * rotation_zpeed * BkTime_DeltaTime();
    BkOrbitalCamera_Rotate(&g_camera, BK_REAL(yaw), BK_REAL(pitch));
  }

  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT)) {
    double dx = (posx - last_mouse_pos[0]) * zoom_speed * BkTime_DeltaTime();
    double dy = (posy - last_mouse_pos[1]) * zoom_speed * BkTime_DeltaTime();
    double radius = dx - dy;
    BkOrbitalCamera_Zoom(&g_camera, BK_REAL(radius));
  }

  last_mouse_pos[0] = posx;
  last_mouse_pos[1] = posy;
}

void ResizeCallback(GLFWwindow* window, int width, int height) {
  (void)window;

  glViewport(0, 0, width, height);
  g_camera.base.projection =
      BkProjection_Perspective(CAMERA_FOV_DEG, BK_REAL(width) / BK_REAL(height),
                               BK_REAL(0.1), BK_REAL(1000));
}

void ErrorCallback(int error, const char* msg) {
  (void)error;

  std::cout << "Fatal: " << msg << std::endl;
  exit(EXIT_FAILURE);
}

void ShowFPS(GLFWwindow* window) {
  static double previous_seconds = 0;
  static int frame_count = 0;

  double elapsed_seconds = 0;

  // Returns number of seconds since GLFW started.
  double currend_seconds = glfwGetTime();

  elapsed_seconds = currend_seconds - previous_seconds;

  // Limit text update 4 times per seconds.
  if (elapsed_seconds > 0.25) {
    previous_seconds = currend_seconds;
    double fps = (double)frame_count / elapsed_seconds;
    double ms_per_frame = 1000.0 / fps;

    std::ostringstream out;

    out.precision(3);

    out << std::fixed << APP_TITLE << "  |  " << "FPS: " << fps << "  |  "
        << "Frame time: " << ms_per_frame << " (ms)";

    glfwSetWindowTitle(window, out.str().c_str());

    frame_count = 0;
  }

  frame_count++;
}