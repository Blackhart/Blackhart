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
#include "ui/PropertiesPanel.hpp"
#include "ui/ScenePanel.hpp"
#include "ui/StudioLayout.hpp"
#include "ui/Toolbar.hpp"
#include "ui/ViewportPanel.hpp"

// Globales
static struct BkOrbitalCamera g_camera;
static BkScene* g_scene = NULL;
static Studio::AssetBrowser g_assets;
static Studio::ViewportPanelState g_viewport;
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
static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
static void ResizeCallback(GLFWwindow* window, int width, int height);
static void ErrorCallback(int error, const char* msg);
static void UpdateCameraProjection(int width, int height);

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
  glfwSetScrollCallback(window, ScrollCallback);
  glfwSetWindowSizeCallback(window, ResizeCallback);

  // Uncapped by default so large clouds show real cost (toolbar can re-enable
  // VSync).
  glfwSwapInterval(0);

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
  int fb_width = 0;
  int fb_height = 0;
  glfwGetWindowSize(window, &width, &height);
  glfwGetFramebufferSize(window, &fb_width, &fb_height);
  ResizeCallback(window, width, height);

  while (!glfwWindowShouldClose(window)) {
    BkTime_Update();
    Studio::Toolbar_Update();

    glfwPollEvents();

    Studio::ImGuiLayer_BeginFrame();
    float const toolbar_h = Studio::Toolbar_Draw();
    g_assets.Draw();
    BkPointCloud* const selected = Studio::ScenePanel_GetSelectedCloud(g_scene);
    bool const aabb_draw = Studio::PropertiesPanel_Draw(selected, &g_camera);
    Studio::ViewportPanel_Draw(toolbar_h, Studio::kSidebarWidth,
                               Studio::kRightSidebarWidth, &g_viewport);

    // Chrome background for regions outside the 3D viewport.
    glDisable(GL_SCISSOR_TEST);
    glViewport(0, 0, fb_width, fb_height);
    glClearColor(0.09f, 0.10f, 0.12f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (g_viewport.framebuffer.width > 0 && g_viewport.framebuffer.height > 0) {
      UpdateCameraProjection(g_viewport.framebuffer.width,
                             g_viewport.framebuffer.height);

      glEnable(GL_SCISSOR_TEST);
      glScissor(g_viewport.framebuffer.x, g_viewport.framebuffer.y,
                g_viewport.framebuffer.width, g_viewport.framebuffer.height);
      glViewport(g_viewport.framebuffer.x, g_viewport.framebuffer.y,
                 g_viewport.framebuffer.width, g_viewport.framebuffer.height);

      BkRender_Clear();

      Studio::ToolbarViewportHelpers const& helpers =
          Studio::Toolbar_GetViewportHelpers();
      if (helpers.grid_visible) {
        BkRender_DrawGrid(&(g_camera.base),
                          static_cast<real>(helpers.grid_cell_size));
      }

      BkRender_DrawScene(g_scene, &(g_camera.base));

      if (selected != nullptr) {
        struct BkAABB const world = BkPointCloud_GetAABB(selected);
        struct BkVector3 const size = BkAABB_Size(&world);
        real axis_len = BkVector3_Magnitude(&size) * BK_REAL(0.25);
        if (axis_len < BK_REAL(0.05)) {
          axis_len = BK_REAL(0.05);
        }
        BkRender_DrawAxes(&(g_camera.base), BkPointCloud_GetTransform(selected),
                          axis_len);
        if (aabb_draw) {
          BkRender_DrawAabb(&(g_camera.base), &world);
        }
      }

      if (helpers.orientation_gizmo_visible) {
        BkRender_DrawOrientationGizmo(&(g_camera.base));
      }

      glDisable(GL_SCISSOR_TEST);
    }

    Studio::ImGuiLayer_EndFrame();
    glfwSwapBuffers(window);

    glfwGetWindowSize(window, &width, &height);
    glfwGetFramebufferSize(window, &fb_width, &fb_height);
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
  // Degrees per pixel (previously 20 * dt @ 60 Hz ≈ 0.33).
  static double rotation_speed = 0.35;
  static bool orbiting = false;

  bool const left_down =
      glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;

  // Orbit only when interacting with the Scene viewport panel.
  if (!left_down) {
    orbiting = false;
  } else if (g_viewport.hovered) {
    orbiting = true;
  }

  if (orbiting) {
    // Mouse delta is already screen-space displacement; do not scale by
    // DeltaTime (that made orbit feel weaker at high uncapped FPS).
    double const yaw = (posx - last_mouse_pos[0]) * rotation_speed;
    double const pitch = (posy - last_mouse_pos[1]) * rotation_speed;
    BkOrbitalCamera_Rotate(&g_camera, BK_REAL(yaw), BK_REAL(pitch));
  }

  last_mouse_pos[0] = posx;
  last_mouse_pos[1] = posy;
}

void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
  (void)window;
  (void)xoffset;

  if (!g_viewport.hovered) {
    return;
  }

  real const zoom_factor = BK_REAL(0.1);
  BkOrbitalCamera_Zoom(&g_camera,
                       BK_REAL(-yoffset) * g_camera.radius * zoom_factor);
}

void UpdateCameraProjection(int width, int height) {
  if (width <= 0 || height <= 0) {
    return;
  }

  g_camera.base.projection =
      BkProjection_Perspective(CAMERA_FOV_DEG, BK_REAL(width) / BK_REAL(height),
                               BK_REAL(0.1), BK_REAL(1000));
}

void ResizeCallback(GLFWwindow* window, int width, int height) {
  (void)window;

  if (width <= 0 || height <= 0) {
    return;
  }

  // Projection is updated each frame from the Scene panel size.
  UpdateCameraProjection(width, height);
}

void ErrorCallback(int error, const char* msg) {
  (void)error;

  std::cout << "Fatal: " << msg << std::endl;
  exit(EXIT_FAILURE);
}
