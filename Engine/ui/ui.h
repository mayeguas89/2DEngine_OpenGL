#pragma once

#include "ui/viewport.h"
#include "utils/singleton.h"

#include <memory>
#include <vector>

class UI: public Singleton<UI>
{
public:
  void Init();
  void Update();
  void End();

private:
  std::vector<std::unique_ptr<Viewport>> viewports_;
};