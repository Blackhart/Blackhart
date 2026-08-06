#include "ui/PerformancePanel.hpp"

#include <GLFW/glfw3.h>
#include <imgui.h>

namespace Studio {

namespace {

double g_previous_seconds = 0.0;
int g_frame_count = 0;
float g_fps = 0.0f;
float g_ms_per_frame = 0.0f;

}  // namespace

void PerformancePanel_Update() {
  double const now = glfwGetTime();
  if (g_previous_seconds == 0.0) {
    g_previous_seconds = now;
  }

  ++g_frame_count;

  double const elapsed = now - g_previous_seconds;
  if (elapsed > 0.25) {
    g_fps = static_cast<float>(g_frame_count / elapsed);
    g_ms_per_frame = (g_fps > 0.0f) ? (1000.0f / g_fps) : 0.0f;
    g_previous_seconds = now;
    g_frame_count = 0;
  }
}

void PerformancePanel_Draw() {
  ImGui::SetNextWindowPos(ImVec2(12.0f, 390.0f), ImGuiCond_FirstUseEver);
  ImGui::SetNextWindowSize(ImVec2(220.0f, 100.0f), ImGuiCond_FirstUseEver);

  if (!ImGui::Begin("Performance")) {
    ImGui::End();
    return;
  }

  ImGui::Text("FPS: %.1f", g_fps);
  ImGui::Text("Frame: %.2f ms", g_ms_per_frame);

  ImGui::End();
}

}  // namespace Studio
