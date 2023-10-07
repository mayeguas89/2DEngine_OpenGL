#include "properties_viewport.h"

#include "imgui.h"

void PropertiesViewport::Draw()
{
  ImGui::Begin(name_.c_str());
  ImGui::Text("Text 1");
  ImGui::Text("Text 2");
  ImGui::Text("Text 3");
  ImGui::End();
}