#pragma once
#include <graphics_engine.h>
#include <inputs.h>

namespace dfe {
struct GameloopInitSettings {
  float updateTime = 0.2f;
};

class Gameloop {
 public:
  Gameloop();
  ~Gameloop() = default;
  void Init();
  void Update(GraphicsEngine* graphicsEnigne, Inputs* inputs);
  void Destroy();

 private:
  bool _isRunning;
  double _elapsedTime;
  double _deltaTime;

  GraphicsEngine* _graphicsEngine;
  Inputs* _inputs;
};
}  // namespace dfe