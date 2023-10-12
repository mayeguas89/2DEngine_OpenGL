#pragma once

#include "common/entity.h"
#include "glm/glm.hpp"
#include "render/gl_texture.h"
#include "render/render_program.h"

#include <memory>

class Sprite2D: public Entity
{
public:
  Sprite2D();
  ~Sprite2D();
  virtual void Draw() override;
  virtual void Update() override
  {
    Entity::Update();
  }

private:
  unsigned int VAO, VBO, VIO, VTO;
  RenderProgram program_;
  std::shared_ptr<GLTexture> texture_;
  glm::vec2 size_;
};