#pragma once
#include "glm/glm.hpp"
class Camera
{
public:
  Camera() = default;
  ~Camera() = default;

  void Update();
  glm::mat4 GetViewMatrix() const;
  glm::mat4 GetProjectionMatrix() const;

  void SetFov(const float fov)
  {
    fov_ = fov;
  }

  void SetLookAt(const glm::vec3& lookAt)
  {
    lookAt_ = lookAt;
  }

  void SetPosition(const glm::vec3& position)
  {
    position_ = position;
  }

private:
  glm::vec3 position_;
  glm::vec3 lookAt_;
  glm::vec3 up_{0.f, 1.f, 0.f};
  float fov_{90.f};
  float nearPlane_{0.1f};
  float farPlane_{100.f};
};