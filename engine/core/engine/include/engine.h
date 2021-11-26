#pragma once
#include <gameloop.h>
#include <graphics_engine.h>
#include <core_system_manager.h>

namespace dfe {
struct EngineInitSettings {};

class Engine : public IQuitInputs {
 public:
  Engine(EngineInitSettings initSettings);
  ~Engine() = default;

  void Run();
  void Stop();
  void Destroy();

  std::function<void()> GetCallbackOnWindowQuitInputs();

 private:
  Gameloop _gameloop;
  CoreSystemManager _coreSystemManager;
};
}  // namespace dfe