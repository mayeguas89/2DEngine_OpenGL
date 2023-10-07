#include "gl_render.h"

#include "common/engine.h"
#include "glad/gl.h"
#include "spdlog/spdlog.h"
#include "ui/ui.h"

namespace
{
static void GlfwErrorCallback(int error, const char* description)
{
  spdlog::error("GLFW Error {}: {}\n", error, description);
}

static void WindowResizeCallback(GLFWwindow* window, int width, int height) {}
}

void GLRender::Init()
{
  glfwSetErrorCallback(GlfwErrorCallback);
  if (!glfwInit())
    throw std::runtime_error("Error initializing glfw");

  spdlog::info("glfw initialized");

  CreateWindow();

  glfwSetWindowUserPointer(window_.get(), this);

  glfwMakeContextCurrent(window_.get());
  glfwSwapInterval(1);
  gladLoadGL(glfwGetProcAddress);

  // glEnable(GL_DEPTH_TEST);
  // glEnable(GL_BLEND);
  // glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

  auto resizefunction = [](GLFWwindow* window, int width, int height)
  {
    auto render = static_cast<GLRender*>(glfwGetWindowUserPointer(window));
    if (!render)
      throw std::runtime_error("Error getting render pointer from glfw window");
    render->WindowResizeCallback(width, height);
  };

  glfwSetWindowSizeCallback(window_.get(), resizefunction);

  UI::Instance().Init();
}

void GLRender::Draw()
{
  UI::Instance().Update();
  // Draw();
}

void GLRender::End()
{
  window_.reset();
  glfwTerminate();
}

void GLRender::Clear()
{
  glClearColor(clearColor_.r, clearColor_.g, clearColor_.b, clearColor_.a);
  // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClear(GL_COLOR_BUFFER_BIT);
}

void GLRender::SwapBuffers()
{
  glfwSwapBuffers(window_.get());
}

bool GLRender::CheckWindowShouldClose()
{
  return glfwWindowShouldClose(window_.get());
}

void GLRender::CreateWindow()
{
  auto window = glfwCreateWindow(windowSize_.x, windowSize_.y, windowTitle_.c_str(), nullptr, nullptr);
  if (!window)
    throw std::runtime_error("Error creating window");

  spdlog::info("Window {}, {} created", windowSize_.x, windowSize_.y);

  window_.reset(window);
}

void GLRender::WindowResizeCallback(int width, int height)
{
  windowSize_ = {width, height};
  glViewport(0, 0, width, height);
  glfwSetWindowSize(window_.get(), width, height);
  spdlog::info("Window resized to {}, {}", width, height);
}
