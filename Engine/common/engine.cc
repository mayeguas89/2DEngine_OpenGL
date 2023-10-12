#include "engine.h"
// clang-format off
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/gl.h"
// clang-format on
#include "common/sprite.h"
#include "render/gl_render.h"

#include <algorithm>
#include <string>

static const int WINDOW_WIDTH = 720;
static const int WINDOW_HEIGHT = 480;
static const std::string APP_NAME = "2DGameEngine";

namespace
{
void CreateRenderTexture(unsigned int& id, const glm::vec<2, int>& size)
{
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
}
void CreateFrameBufferAndAttachToRenderTexture(unsigned int& id,
                                               const glm::vec<2, int>& size,
                                               unsigned int& textureId)
{
  glGenFramebuffers(1, &id);
  glBindFramebuffer(GL_FRAMEBUFFER, id);
  unsigned int fbId;
  glGenRenderbuffers(1, &fbId);
  glBindRenderbuffer(GL_RENDERBUFFER, fbId);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, size.x, size.y);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, fbId);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId, 0);
}
}

void Engine::Init()
{
  auto& render = GLRender::Instance();
  render.SetWindowSize({WINDOW_WIDTH, WINDOW_HEIGHT});
  render.SetWindowTitle(APP_NAME);
  render.Init();

  // Create texture to render to
  CreateRenderTexture(textureId_, render.GetWindowSize());
  // Attach frame buffer
  CreateFrameBufferAndAttachToRenderTexture(frameBufferId_, render.GetWindowSize(), textureId_);

  entities_.push_back(std::make_shared<Sprite2D>());
  mainCamera_.SetPosition(glm::vec3{0.f, 0.f, -1.f});
  mainCamera_.SetLookAt(glm::vec3{0.f, 0.f, 0.f});
  isRunning_ = true;
}

void Engine::Run()
{
  auto& render = GLRender::Instance();
  while (isRunning_)
  {
    glfwPollEvents();
    render.Clear();
    //  Updates
    std::for_each(entities_.begin(), entities_.end(), [](auto& entity) { entity->Update(); });

    render.Draw();
    render.SwapBuffers();

    isRunning_ = !render.CheckWindowShouldClose();
  }
}

void Engine::End()
{
  GLRender::Instance().End();
}

std::shared_ptr<GLTexture> Engine::GetTexture(const std::string& filename)
{
  auto it = textureMap_.find(filename);
  if (it == textureMap_.end())
  {
    auto texture = std::make_shared<GLTexture>();
    texture->LoadFromFile(filename);
    auto [iterator, _] = textureMap_.insert({filename, std::move(texture)});
    it = iterator;
  }
  auto& [_, texture] = *it;
  return texture;
}

void Engine::ResizeFrameBuffer(const glm::vec<2, int>& windowSize)
{
  // Delete old texture and frame buffer to create a new ones with the appropiate size
  glDeleteTextures(1, &textureId_);
  // Create texture to render to
  CreateRenderTexture(textureId_, windowSize);
  // Attach frame buffer
  glDeleteFramebuffers(1, &frameBufferId_);
  CreateFrameBufferAndAttachToRenderTexture(frameBufferId_, windowSize, textureId_);
}
