#pragma once

#include "glm/glm.hpp"

#include <string>

class Entity
{
public:
  Entity()
  {
    id_++;
  }

  virtual void Update() = 0;

  glm::mat4 GetModelMatrix() const
  {
    return modelMatrix_;
  }

  glm::vec4 GetPosition() const
  {
    return position_;
  }

  glm::vec4 GetRotation() const
  {
    return rotation_;
  }

  glm::vec4 GetScale() const
  {
    return scale_;
  }

  virtual void Draw() = 0;

protected:
  void ComputeModelMatrix();
  inline static unsigned int id_;
  std::string tag_;

  glm::vec4 position_{0.f, 0.f, 0.f, 0.f};
  glm::vec4 rotation_{0.f, 0.f, 0.f, 0.f};
  glm::vec4 scale_{1.f, 1.f, 1.f, 0.f};

  glm::mat4 modelMatrix_;
};
