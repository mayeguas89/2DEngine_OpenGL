#include "engine.h"

#include "GLFW/glfw3.h"
#include "render/gl_render.h"

#include <string>

static const int WINDOW_WIDTH = 720;
static const int WINDOW_HEIGHT = 480;
static const std::string APP_NAME = "2DGameEngine";

void Engine::Init()
{
  auto& render = GLRender::Instance();
  render.SetWindowSize({WINDOW_WIDTH, WINDOW_HEIGHT});
  render.SetWindowTitle(APP_NAME);
  render.Init();

  isRunning_ = true;
}

void Engine::Run()
{
  auto& render = GLRender::Instance();
  while (isRunning_)
  {
    glfwPollEvents();
    render.Clear();
    render.Draw();
    render.SwapBuffers();

    isRunning_ = !render.CheckWindowShouldClose();
  }
}

void Engine::End()
{
  GLRender::Instance().End();
}
