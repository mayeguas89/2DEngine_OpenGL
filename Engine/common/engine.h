#pragma once

#include "utils/singleton.h"

class Engine: public Singleton<Engine>
{
public:
  void Init();
  void Run();
  void End();

private:
  bool isRunning_{false};
};