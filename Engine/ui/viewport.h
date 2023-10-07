#pragma once

#include <string>

class Viewport
{
public:
  Viewport(const std::string& name): name_{name} {}
  virtual ~Viewport() = default;

  virtual void Draw() = 0;

  std::string GetName() const
  {
    return name_;
  }

protected:
  std::string name_;
};