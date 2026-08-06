#include "ui/ImGuiLayer.hpp"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace Studio {

namespace {

void ApplyStudioStyle() {
  ImGui::StyleColorsDark();

  ImGuiStyle& style = ImGui::GetStyle();
  style.WindowRounding = 8.0f;
  style.ChildRounding = 6.0f;
  style.FrameRounding = 4.0f;
  style.PopupRounding = 6.0f;
  style.ScrollbarRounding = 6.0f;
  style.GrabRounding = 3.0f;
  style.TabRounding = 4.0f;
  style.WindowBorderSize = 0.0f;
  style.FrameBorderSize = 0.0f;
  style.WindowPadding = ImVec2(14.0f, 12.0f);
  style.FramePadding = ImVec2(10.0f, 6.0f);
  style.ItemSpacing = ImVec2(10.0f, 8.0f);
  style.ItemInnerSpacing = ImVec2(8.0f, 5.0f);
  style.ScrollbarSize = 12.0f;
  style.GrabMinSize = 12.0f;

  ImVec4* c = style.Colors;
  // Charcoal surfaces (mockup-like), teal accents — not purple.
  c[ImGuiCol_Text] = ImVec4(0.92f, 0.93f, 0.94f, 1.00f);
  c[ImGuiCol_TextDisabled] = ImVec4(0.55f, 0.56f, 0.58f, 1.00f);
  c[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.12f, 0.14f, 0.97f);
  c[ImGuiCol_ChildBg] = ImVec4(0.09f, 0.10f, 0.11f, 1.00f);
  c[ImGuiCol_PopupBg] = ImVec4(0.12f, 0.13f, 0.15f, 0.98f);
  c[ImGuiCol_Border] = ImVec4(0.22f, 0.23f, 0.26f, 0.60f);
  c[ImGuiCol_FrameBg] = ImVec4(0.16f, 0.17f, 0.20f, 1.00f);
  c[ImGuiCol_FrameBgHovered] = ImVec4(0.20f, 0.22f, 0.26f, 1.00f);
  c[ImGuiCol_FrameBgActive] = ImVec4(0.24f, 0.26f, 0.30f, 1.00f);
  c[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.10f, 0.11f, 1.00f);
  c[ImGuiCol_TitleBgActive] = ImVec4(0.09f, 0.10f, 0.11f, 1.00f);
  c[ImGuiCol_TitleBgCollapsed] = ImVec4(0.09f, 0.10f, 0.11f, 1.00f);
  c[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.11f, 0.13f, 1.00f);
  c[ImGuiCol_ScrollbarBg] = ImVec4(0.08f, 0.09f, 0.10f, 1.00f);
  c[ImGuiCol_ScrollbarGrab] = ImVec4(0.28f, 0.30f, 0.34f, 1.00f);
  c[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.34f, 0.36f, 0.40f, 1.00f);
  c[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.40f, 0.42f, 0.46f, 1.00f);
  c[ImGuiCol_CheckMark] = ImVec4(0.35f, 0.78f, 0.82f, 1.00f);
  c[ImGuiCol_SliderGrab] = ImVec4(0.35f, 0.78f, 0.82f, 1.00f);
  c[ImGuiCol_SliderGrabActive] = ImVec4(0.45f, 0.88f, 0.90f, 1.00f);
  c[ImGuiCol_Button] = ImVec4(0.18f, 0.32f, 0.34f, 1.00f);
  c[ImGuiCol_ButtonHovered] = ImVec4(0.25f, 0.45f, 0.48f, 1.00f);
  c[ImGuiCol_ButtonActive] = ImVec4(0.30f, 0.55f, 0.58f, 1.00f);
  c[ImGuiCol_Header] = ImVec4(0.20f, 0.36f, 0.40f, 0.80f);
  c[ImGuiCol_HeaderHovered] = ImVec4(0.28f, 0.50f, 0.55f, 0.90f);
  c[ImGuiCol_HeaderActive] = ImVec4(0.32f, 0.58f, 0.62f, 1.00f);
  c[ImGuiCol_Separator] = ImVec4(0.24f, 0.25f, 0.28f, 1.00f);
  c[ImGuiCol_ResizeGrip] = ImVec4(0.35f, 0.78f, 0.82f, 0.25f);
  c[ImGuiCol_ResizeGripHovered] = ImVec4(0.35f, 0.78f, 0.82f, 0.50f);
  c[ImGuiCol_ResizeGripActive] = ImVec4(0.35f, 0.78f, 0.82f, 0.75f);
}

}  // namespace

void ImGuiLayer_Init(GLFWwindow* window) {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ApplyStudioStyle();

  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

  // Chain with callbacks already installed by the studio (mouse / keys).
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 430");
}

void ImGuiLayer_Shutdown() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void ImGuiLayer_BeginFrame() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void ImGuiLayer_EndFrame() {
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

}  // namespace Studio
