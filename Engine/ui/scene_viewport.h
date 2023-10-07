#pragma once

#include "ui/viewport.h"

class SceneViewport: public Viewport
{
public:
  SceneViewport(const std::string& name): Viewport{name} {}

  virtual void Draw() override;

private:
};