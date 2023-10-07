#include "scene_viewport.h"

#include "imgui.h"

void SceneViewport::Draw()
{
  ImGui::Begin(name_.c_str());
  ImGui::End();
}