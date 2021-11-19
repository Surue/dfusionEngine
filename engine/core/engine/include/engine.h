#pragma once
#include <gameloop.h>
#include <graphics_engine.h>
#include <inputs.h>

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
  Inputs _inputs;
};
}  // namespace dfe