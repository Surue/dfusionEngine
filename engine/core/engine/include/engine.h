#pragma once
#include <gameloop.h>

namespace dfe {
struct EngineInitSettings {};

class Engine {
 public:
  Engine(EngineInitSettings initSettings);
  ~Engine() = default;

  void Run();

 private:
  Gameloop _gameloop;
};
}  // namespace dfe