#pragma once

#include "common/entity.h"
#include "glm/glm.hpp"
#include "render/gl_texture.h"
#include "render/render_program.h"

class Sprite2D: public Entity
{
public:
  Sprite2D();
  virtual void Draw() override;
  virtual void Update() override
  {
    Entity::Update();
  }

private:
  unsigned int VAO, VBO, VIO, VTO;
  RenderProgram program_;
  GLTexture* texture_;
  glm::vec2 size_;
};