#pragma once
#include <graphics_engine.h>

namespace dfe {
struct GameloopInitSettings {
  float updateTime = 0.2f;
};

class Gameloop {
 public:
  Gameloop();
  ~Gameloop() = default;
  void Init();
  void Update(GraphicsEngine* graphicsEnigne);
  void Destroy();

 private:
  bool _isRunning;
  double _elapsedTime;
  double _deltaTime;

  GraphicsEngine* _graphicsEngine;
};
}  // namespace dfe