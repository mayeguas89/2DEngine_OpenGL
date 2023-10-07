add_executable(
  ${PROJECT_NAME} 
  main.cc
  common/engine.cc
  render/gl_render.cc
  ui/ui.cc
  ui/scene_graph_viewport.cc
  ui/scene_viewport.cc
  ui/properties_viewport.cc
)

target_include_directories(${PROJECT_NAME} PRIVATE 
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${GLAD_DIR}/include
  ${GLFW_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/external/imgui
  ${CMAKE_SOURCE_DIR}/external/imgui/backends
)

target_link_libraries(${PROJECT_NAME} 
 PRIVATE
#  argparse::argparse
 glad
 glfw
 glm
 Imgui
 spdlog::spdlog
#  nlohmann_json::nlohmann_json
)