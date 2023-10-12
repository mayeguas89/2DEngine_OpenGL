#include "scene_viewport.h"

#include "common/engine.h"
#include "imgui.h"

void SceneViewport::Draw()
{
  ImGui::Begin(name_.c_str());
  ImVec2 viewportPanelSize = ImGui::GetWindowSize();
  ImGui::Image((void*)(intptr_t)Engine::Instance().textureId_, viewportPanelSize);
  ImGui::End();
}