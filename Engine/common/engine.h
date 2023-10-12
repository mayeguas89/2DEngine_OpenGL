#pragma once

#include "common/camera.h"
#include "common/entity.h"
#include "render/gl_texture.h"
#include "utils/singleton.h"

#include <memory>
#include <unordered_map>

class Engine: public Singleton<Engine>
{
public:
  void Init();
  void Run();
  void End();

  std::shared_ptr<GLTexture> GetTexture(const std::string& filename);

  std::vector<std::shared_ptr<Entity>> GetEntities() const
  {
    return entities_;
  }

  void AddEntity(std::shared_ptr<Entity>& entity)
  {
    entities_.push_back(std::move(entity));
  }

  const Camera& GetMainCamera() const
  {
    return mainCamera_;
  }

  void ResizeFrameBuffer(const glm::vec<2, int>& windowSize);

  unsigned int textureId_ = 0;
  unsigned int frameBufferId_ = 0;

private:
  bool isRunning_{false};
  std::vector<std::shared_ptr<Entity>> entities_;
  std::unordered_map<std::string, std::shared_ptr<GLTexture>> textureMap_;
  Camera mainCamera_;
};