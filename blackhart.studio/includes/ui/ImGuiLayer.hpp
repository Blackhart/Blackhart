#ifndef __BK_STUDIO_IMGUI_LAYER_HPP__
#define __BK_STUDIO_IMGUI_LAYER_HPP__

struct GLFWwindow;

namespace Studio {

void ImGuiLayer_Init(GLFWwindow* window);
void ImGuiLayer_Shutdown();
void ImGuiLayer_BeginFrame();
void ImGuiLayer_EndFrame();

}  // namespace Studio

#endif
