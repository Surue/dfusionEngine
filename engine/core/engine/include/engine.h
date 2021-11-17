#pragma once
#include <gameloop.h>
#include <graphics_engine.h>

namespace dfe {
struct EngineInitSettings {};

class Engine {
 public:
  Engine(EngineInitSettings initSettings);
  ~Engine() = default;

  void Run();

 private:
  Gameloop _gameloop;
  GraphicsEngine _graphicsEngine;
};
}  // namespace dfe