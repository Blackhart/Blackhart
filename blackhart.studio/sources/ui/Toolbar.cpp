#include "ui/Toolbar.hpp"

#include <GLFW/glfw3.h>
#include <imgui.h>

#include <cstdio>

#include "../../blackhart/export/cpp/Blackhart.hpp"
#include "ui/StudioLayout.hpp"

namespace Studio {

namespace {

double g_previous_seconds = 0.0;
int g_frame_count = 0;
float g_fps = 0.0f;
float g_ms_per_frame = 0.0f;
bool g_vsync = false;

ToolbarViewportHelpers g_helpers = {};

/** Vertical rule between toolbar control groups. */
void Toolbar_VerticalSep() {
  ImGui::SameLine(0.0f, 18.0f);
  ImVec2 const p = ImGui::GetCursorScreenPos();
  float const h = ImGui::GetFrameHeight();
  ImGui::GetWindowDrawList()->AddLine(
      ImVec2(p.x, p.y + 3.0f), ImVec2(p.x, p.y + h - 3.0f),
      ImGui::GetColorU32(ImVec4(0.38f, 0.40f, 0.44f, 1.00f)), 1.0f);
  ImGui::Dummy(ImVec2(1.0f, h));
  ImGui::SameLine(0.0f, 18.0f);
}

}  // namespace

void Toolbar_Update() {
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

float Toolbar_Draw() {
  ImGuiViewport const* viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(viewport->WorkPos);
  ImGui::SetNextWindowSize(ImVec2(viewport->WorkSize.x, kToolbarHeight));

  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(16.0f, 10.0f));
  ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.09f, 0.10f, 0.12f, 1.00f));

  ImGuiWindowFlags const flags =
      ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
      ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar |
      ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoSavedSettings |
      ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

  if (!ImGui::Begin("##StudioToolbar", nullptr, flags)) {
    ImGui::End();
    ImGui::PopStyleColor();
    ImGui::PopStyleVar(3);
    return kToolbarHeight;
  }

  float const bar_w = ImGui::GetContentRegionAvail().x;
  float const row_y = ImGui::GetCursorPosY();

  // Left — brand
  ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX(), row_y + 2.0f));
  ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.95f, 0.96f, 0.97f, 1.00f));
  ImGui::TextUnformatted("Blackhart Studio");
  ImGui::PopStyleColor();
  ImGui::SameLine(0.0f, 10.0f);
  ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.50f, 0.52f, 0.55f, 1.00f));
  ImGui::TextUnformatted("Point Cloud Viewer");
  ImGui::PopStyleColor();

  // Center — point size + grid + orientation gizmo
  float point_size = static_cast<float>(BkRender_GetPointSize());
  bool point_changed = false;

  float const center_block_w = 720.0f;
  float const center_x = (bar_w - center_block_w) * 0.5f;
  ImGui::SetCursorPos(ImVec2(center_x, row_y));

  ImGui::AlignTextToFramePadding();
  ImGui::TextUnformatted("Point size");
  ImGui::SameLine();
  ImGui::SetNextItemWidth(110.0f);
  point_changed |=
      ImGui::SliderFloat("##point_size_slider", &point_size, 1.0f, 32.0f, "");
  ImGui::SameLine();
  ImGui::SetNextItemWidth(56.0f);
  point_changed |=
      ImGui::InputFloat("##point_size_input", &point_size, 0.0f, 0.0f, "%.2f");

  Toolbar_VerticalSep();
  ImGui::Checkbox("Grid", &g_helpers.grid_visible);
  ImGui::SameLine();
  ImGui::AlignTextToFramePadding();
  ImGui::TextUnformatted("Cell");
  ImGui::SameLine();
  ImGui::SetNextItemWidth(56.0f);
  ImGui::InputFloat("##grid_cell_input", &g_helpers.grid_cell_size, 0.0f, 0.0f,
                    "%.2f");
  if (g_helpers.grid_cell_size < 0.01f) {
    g_helpers.grid_cell_size = 0.01f;
  }

  Toolbar_VerticalSep();
  ImGui::Checkbox("Axes", &g_helpers.orientation_gizmo_visible);

  Toolbar_VerticalSep();
  if (ImGui::Checkbox("VSync", &g_vsync)) {
    glfwSwapInterval(g_vsync ? 1 : 0);
  }

  if (point_changed) {
    BkRender_SetPointSize(static_cast<real>(point_size));
  }

  // Right — FPS + frame time
  char fps_buf[64];
  std::snprintf(fps_buf, sizeof(fps_buf), "FPS %.0f  %.1f ms", g_fps,
                g_ms_per_frame);
  float const fps_w = ImGui::CalcTextSize(fps_buf).x;
  ImGui::SetCursorPos(
      ImVec2(bar_w - fps_w - ImGui::GetStyle().WindowPadding.x, row_y + 4.0f));
  ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.45f, 0.82f, 0.86f, 1.00f));
  ImGui::TextUnformatted(fps_buf);
  ImGui::PopStyleColor();

  ImGui::End();
  ImGui::PopStyleColor();
  ImGui::PopStyleVar(3);
  return kToolbarHeight;
}

ToolbarViewportHelpers const& Toolbar_GetViewportHelpers() { return g_helpers; }

}  // namespace Studio
