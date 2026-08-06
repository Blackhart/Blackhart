// Standard library headers.
#include <cmath>
#include <iostream>

// Graphics library headers.
#include <GLFW/glfw3.h>

// ImGui
#include <imgui.h>

// blackhart headers.
#include "../../blackhart/export/cpp/Blackhart.hpp"

// blackhart.studio headers.
#include "foundation/BkTime.hpp"
#include "ui/AssetBrowser.hpp"
#include "ui/ImGuiLayer.hpp"
#include "ui/PerformancePanel.hpp"

// Globales
static struct BkOrbitalCamera g_camera;
static BkScene* g_scene = NULL;
static Studio::AssetBrowser g_assets;
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

// ~~~~~ Def(ALL) ~~~~~

int main() {
  // ~~~~~ GLFW INITIALIZATION ~~~~~~

  if (!glfwInit()) return EXIT_FAILURE;

  glfwSetErrorCallback(ErrorCallback);

  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
  glfwWindowHint(GLFW_DEPTH_BITS, DEPTH_BUFFER_BITS);

  GLFWwindow* window = NULL;

  if (g_full_screen) {
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    GLFWvidmode const* vid_mode = glfwGetVideoMode(monitor);

    if (vid_mode != NULL)
      window = glfwCreateWindow(vid_mode->width, vid_mode->height, APP_TITLE,
                                monitor, NULL);
  } else {
    uint16 const window_width = 1100;
    uint16 const window_height = 700;

    window =
        glfwCreateWindow(window_width, window_height, APP_TITLE, NULL, NULL);
  }

  if (window == NULL) {
    glfwTerminate();
    return EXIT_FAILURE;
  }

  glfwMakeContextCurrent(window);

  // Install studio callbacks before ImGui so ImGui can chain to them.
  glfwSetKeyCallback(window, InputCallback);
  glfwSetCursorPosCallback(window, MouseCallback);
  glfwSetWindowSizeCallback(window, ResizeCallback);

  glfwSwapInterval(1);

  // ~~~~~ BLACKHART INITIALIZATION ~~~~~

  BkInitialize();

  g_scene = BkScene_Create();
  if (g_scene == NULL) {
    std::cout << "Fatal: failed to create scene" << std::endl;
    BkUninitialize();
    glfwDestroyWindow(window);
    glfwTerminate();
    return EXIT_FAILURE;
  }

  BkOrbitalCamera_Initialize(&g_camera);

  Studio::ImGuiLayer_Init(window);
  g_assets.Initialize(g_scene, &g_camera, CAMERA_FOV_DEG, CAMERA_FRAME_MARGIN);

  // ~~~~~ RENDER LOOP ~~~~~

  int width = 0;
  int height = 0;
  glfwGetWindowSize(window, &width, &height);
  ResizeCallback(window, width, height);

  while (!glfwWindowShouldClose(window)) {
    BkTime_Update();
    Studio::PerformancePanel_Update();

    glfwPollEvents();

    Studio::ImGuiLayer_BeginFrame();
    g_assets.Draw();
    Studio::PerformancePanel_Draw();

    BkRender(g_scene, &(g_camera.base));

    Studio::ImGuiLayer_EndFrame();
    glfwSwapBuffers(window);
  }

  // ~~~~~ BLACKHART UNINITIALIZATION ~~~~~

  g_assets.Shutdown();
  Studio::ImGuiLayer_Shutdown();
  BkScene_Release(&g_scene);
  BkUninitialize();

  glfwDestroyWindow(window);
  glfwTerminate();

  return EXIT_SUCCESS;
}

void InputCallback(GLFWwindow* window, int key, int scancode, int action,
                   int mods) {
  (void)mods;
  (void)scancode;

  ImGuiIO const& io = ImGui::GetIO();
  if (io.WantCaptureKeyboard) {
    return;
  }

  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void MouseCallback(GLFWwindow* window, double posx, double posy) {
  static double last_mouse_pos[2] = {0.0, 0.0};
  static double rotation_speed = 20.0;
  static double zoom_speed = 3.0;

  ImGuiIO const& io = ImGui::GetIO();
  if (!io.WantCaptureMouse) {
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == 1) {
      double yaw =
          (posx - last_mouse_pos[0]) * rotation_speed * BkTime_DeltaTime();
      double pitch =
          (posy - last_mouse_pos[1]) * rotation_speed * BkTime_DeltaTime();
      BkOrbitalCamera_Rotate(&g_camera, BK_REAL(yaw), BK_REAL(pitch));
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT)) {
      double dx = (posx - last_mouse_pos[0]) * zoom_speed * BkTime_DeltaTime();
      double dy = (posy - last_mouse_pos[1]) * zoom_speed * BkTime_DeltaTime();
      double radius = dx - dy;
      BkOrbitalCamera_Zoom(&g_camera, BK_REAL(radius));
    }
  }

  last_mouse_pos[0] = posx;
  last_mouse_pos[1] = posy;
}

void ResizeCallback(GLFWwindow* window, int width, int height) {
  (void)window;

  if (width <= 0 || height <= 0) {
    return;
  }

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
